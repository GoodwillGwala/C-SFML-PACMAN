/**
*@class <Tile>
*@brief This class provides the definition of a tile node and it's characteristics
*/
#ifndef TILE_H
#define TILE_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "SpriteNode.h"

class Tile : public SpriteNode
{
	public:

	    /**
        *@enum <Type>
        *@brief enum identify different tiles
        */
	    enum Type
	    {
	        Wall,
	        TypeCount
	    };

        /**
        *@brief Constructor
        *@param textures and type of tile
        *tile is a wall by default
        */
		explicit			            Tile(const TextureHolder& textures, Type type = Type::Wall );
		/**
        *@brief function to set tile position
        *@param position vector
        *This function sets the sprite position that respresents the tile
        */
        void                            setPosition(const sf::Vector2f& position);
        /**
        *@brief function to get information about tile size
        *@return returns a size vector
        *this size is retrieved from the data tables
        */
        sf::Vector2f                    getSize();
        /**
        * @brief function that facilitates the querying the category
        * @return Category based on the type of tile
        */
        virtual unsigned int	        getCategory() const;
        /**
        * @brief function that facilitates the querying of tile boundaries
        * @return bounding rectangle
        */
        virtual sf::FloatRect	        getBoundingRect() const;

	private:


        Type                            mType;

};

#endif
