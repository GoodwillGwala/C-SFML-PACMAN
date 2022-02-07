/**
∗ @class <Component>
∗ @brief This class models a node component that is represented in the game world as well as is basic responsibilities.
*/
#ifndef COMPONENT_H
#define COMPONENT_H

#include "Category.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <set>
#include <memory>
#include <utility>


struct Command;
class CommandQueue;

class Component : public sf::Transformable, public sf::Drawable
{
	public:
		typedef std::unique_ptr<Component>          Ptr;
		typedef std::pair<Component*, Component*>   Pair;


	public:

        /**
        * @brief Constructor
        * @param Category
        *
        */
		explicit				Component(Category::Type category = Category::None);
        Component ( const Component& )              = delete;
	    Component& operator= ( const Component& )   = delete;
		/**
        * @brief function to add a child component to it's parent
        * @param node
        *
        *The node of a child to be attached to it's parent is passed in
        */
		void					attachChild(Ptr child);
        /**
        * @brief function to facilitate sequential call of update to node update and children
        *
        */
		void					update(sf::Time dt, CommandQueue& commands);
		/**
        * @brief function the gives information about the nodes position in the game world
        *
        * Global position of node
        * @return position vector
        */

		sf::Vector2f			getWorldPosition() const;
		/**
        * @brief function the gives information about the nodes transformation
        *
        * Node transformation includes, scale, rotation, translation etc relative to game world
        *
        * @return transform
        */

		sf::Transform			getWorldTransform() const;
        /**
        * @brief function that facilitates distribution of commands to a node tree
        *
        * This function facilitates the dispatch of commands to nodes and their children
        *
        *
        * @param Command, Time
        */
		void					onCommand(const Command& command, sf::Time dt);
		/**
        * @brief function that facilitates the querying of a nodes category
        * @return Category
        */

		virtual unsigned int	getCategory() const;

        /**
        * @brief function that facilitates the querying of node collisions between node graphs
        * @param node graph, collision nodes
        *
        */
		void					checkSceneCollision(Component& sceneGraph, std::set<Pair>& collisionPairs);
		/**
        * @brief function that facilitates the querying of node collisions
        * @param node, collision pair nodes
        *
        */
		void					checkNodeCollision(Component& node, std::set<Pair>& collisionPairs);
		/**
        * @brief function that facilitates the removal of destroyed nodes
        */
		void					removeWrecks();
		/**
        * @brief function that facilitates the querying of a nodes boundaries
        * @return bounding rectangle
        */
		virtual sf::FloatRect	getBoundingRect() const;
		/**
        * @brief function that facilitates the querying whether a node should be removed
        * @return bool
        */
		virtual bool			isMarkedForRemoval() const;
		/**
        * @brief function that facilitates the querying whether a node has been destroyed
        *  A destroyed object is marked for removal
        * @return bool
        */
		virtual bool			isDestroyed() const;


	private:

		/**
        * @brief function provides the interface to update a node
        *
        * @param Time, Command Queue
        */
		virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
		/**
        * @brief function that facilitates the sequential updating of node children and command dispatch
        *
        * @param Time, Command Queue
        */
		void					updateChildren(sf::Time dt, CommandQueue& commands);
        /**
        * @brief function that facilitates sequential call of draw
        *
        * @param RenderTarget, RenderStates
        */
		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
		/**
        * @brief function that provides the interface to draw a node
        *
        * @param RenderTarget, RenderStates
        */
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		/**
        * @brief function that facilitates the drawing of node children
        *
        * @param RenderTarget, RenderStates
        */
		void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
		/**
        * @brief function that facilitates the drawing of an objects boundaries
        *
        * @param RenderTarget, RenderStates
        */
		void					drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		std::vector<Ptr>		mChildren;
		Component*				mParent;
		Category::Type			mDefaultCategory;
};

        /**
        * @brief stand-alone function that facilitates the querying of node collision.
        * This function uses boundary intersection
        * @return bool
        * returns whether there is an intersection or not
        */
        bool	               collision(const Component& lhs, const Component& rhs);
        /**
        * @brief stand-alone function that facilitates the querying of node distance.
        * This function uses world position to calculate distance between nodes
        * @return distance
        * returns distance between objects
        */
        float	               distance(const Component& lhs, const Component& rhs);

#endif
