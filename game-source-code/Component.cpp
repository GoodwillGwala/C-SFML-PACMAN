#include "Component.h"
#include "Command.h"
#include "Foreach.h"
#include "Utility.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>


Component::Component(Category::Type category)
: mChildren()
, mParent(nullptr)
, mDefaultCategory(category)
{
}

void Component::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

//Component::Ptr Component::detachChild(const Component& node)
//{
//	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (Ptr& p) { return p.get() == &node; });
//	assert(found != mChildren.end());
//
//	Ptr result = std::move(*found);
//	result->mParent = nullptr;
//	mChildren.erase(found);
//	return result;
//}

void Component::update(sf::Time dt, CommandQueue& commands)
{
	updateCurrent(dt, commands);
	updateChildren(dt, commands);
}

void Component::updateCurrent(sf::Time, CommandQueue&)
{
	// Do nothing by default
}

void Component::updateChildren(sf::Time dt, CommandQueue& commands)
{
	FOREACH(Ptr& child, mChildren)
		child->update(dt, commands);
}


void Component::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);


}

void Component::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void Component::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const Ptr&  child : mChildren)
	child->draw(target, states);

//	FOREACH(const Ptr& child, mChildren)
//		child->draw(target, states);
}

void Component::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

sf::Vector2f Component::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform Component::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const Component* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}

void Component::onCommand(const Command& command, sf::Time dt)
{
	// Command current node, if category matches
	if (command.category & getCategory())
		command.action(*this, dt);



	// Command children
	FOREACH(Ptr& child, mChildren)
		child->onCommand(command, dt);
}

unsigned int Component::getCategory() const
{
	return mDefaultCategory;
}

void Component::checkSceneCollision(Component& sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);

	FOREACH(Ptr& child, sceneGraph.mChildren)
		checkSceneCollision(*child, collisionPairs);
}

void Component::checkNodeCollision(Component& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
		collisionPairs.insert(std::minmax(this, &node));

	FOREACH(Ptr& child, mChildren)
		child->checkNodeCollision(node, collisionPairs);
}



void Component::removeWrecks()
{
	// Remove all children which request so
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&Component::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());

	// Call function recursively for all remaining children
	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&Component::removeWrecks));
}

sf::FloatRect Component::getBoundingRect() const
{
	return sf::FloatRect();
}

bool Component::isMarkedForRemoval() const
{
	// By default, remove node if entity is destroyed
	return isDestroyed();
}

bool Component::isDestroyed() const
{
	// By default, scene node needn't be removed
	return false;
}
//  stand-alone functions
bool collision(const Component& lhs, const Component& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

float distance(const Component& lhs, const Component& rhs)
{
	return length( lhs.getWorldPosition() - rhs.getWorldPosition());
}
