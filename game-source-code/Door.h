/**
∗ @class <Door>
∗ @brief This class provides the definition and characteristics of a door tile
*/
#ifndef DOOR_H
#define DOOR_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include <SFML/Graphics/Sprite.hpp>
#include "Entity.h"

class Door : public Entity
{
	public:

	    /**
        *@enum <Type>
        *@brief enum identify different types of doors
        */
	    enum Type
	    {
	        OneWay,
	        TwoWay,
	        TypeCount
	    };


		/**
        *@brief Constructor
        *@param textures and type of door
        *Door is a OneWay by default
        */
		explicit			        Door(const TextureHolder& textures, Type type = Type::OneWay );
        /**
        *@brief function to set door position
        *@param position vector
        *This function sets the sprite position that respresents the door
        */
        void                        setPosition(const sf::Vector2f& position);
	private:


	    virtual void		        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	    virtual sf::FloatRect       getBoundingRect() const override;
        virtual unsigned int	    getCategory() const override;
        sf::Vector2f                getSize();

        Type                        mType;
        sf::Sprite                  mSprite;
};

#endif
