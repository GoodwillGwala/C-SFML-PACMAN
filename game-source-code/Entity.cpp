#include "Entity.h"

#include <cassert>
#include <iostream>

Entity::Entity(int Health)
: mVelocity()
, mHealth(Health)
, mPoints(0)
, mPickups(0)
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}


int Entity::getScore() const
{
	return mPoints;
}

void Entity::reward(int points)
{
	assert(points > 0);

	mPoints += points;

	mPickups++;


}

void Entity::damage()
{

	mHealth -= 1;
}

int Entity::getHealth()
{
    return mHealth;

}

int Entity::pickupcount()
{
    return mPickups;

}

void Entity::destroy()
{
	mHealth = 0;
}

bool Entity::isDestroyed() const
{
	return mHealth <= 0;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue&)
{
	move(mVelocity * dt.asSeconds());
}
