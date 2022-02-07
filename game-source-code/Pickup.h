/**
*@class <Pickup>
*@brief This class provides the interface for pausing gameplay
*/

#ifndef PICKUP_H
#define PICKUP_H

#include "Entity.h"
#include "Command.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>


class GameObject;
class Maze;

class Pickup : public Entity
{
public:

        /**
        ∗ @enum <Type>
        ∗ @brief enum to identify different types of pickups
        */
		enum Type
		{
			Food,
			Food2,
			Food3,

			Key,

			Pallet,
			Pallet2,

			SuperPallet,
			Super2,
			Super3,

			TypeCount
		};


public:
	    /**
        * @brief Constructor
        * @param textures and Type of pickup
        *
        */
								Pickup(const TextureHolder& textures, Type type=Type::Food);
								Pickup();
        /**
        * @brief function that gives information about pickup category based on type
        * @return Category
        */

		virtual unsigned int	getCategory() const;
		/**
        * @brief function that  gives information about pickup boundaries
        * @return bounding rectangle
        */
		virtual sf::FloatRect	getBoundingRect() const;
        /**
        * @brief function that applies the pickup to a Game Object
        * @param Game Object to which the effect of the pick is to be applied and the category (type) of pickup
        */
		void 					apply(GameObject& player, unsigned int category) const;
		/**
        * @brief function that applies the pickup to the Maze
        * @param Maze Object to which the effect of the pick is to be applied
        */
		void                    apply(Maze& maze) const;


protected:
		/**
        * @brief function that provides the interface to render drawable objects to a target
        *
        * @param RenderTarget, RenderStates
        */
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
		Type 					mType;
		sf::Sprite				mSprite;
};

#endif
