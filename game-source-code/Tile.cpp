#include "Tile.h"
#include "DataTables.h"
#include "Category.h"

#include "Utility.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace
{
	const std::vector<TileData> Table = initializeTileData();
}

Tile::Tile( const TextureHolder& textures, Type type)
: mType(type)
, SpriteNode(textures.get(Table[type].texture))
{

}

unsigned int Tile::getCategory() const
{

	return Category::Wall;
}

void Tile::setPosition(const sf::Vector2f& position)
{

    mSprite.setPosition(position);

}

sf::FloatRect Tile::getBoundingRect() const
{
	return mSprite.getGlobalBounds();
}


sf::Vector2f Tile:: getSize()
{
   return    Table[mType].size;

}
