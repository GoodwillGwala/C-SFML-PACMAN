#include "Door.h"
#include "DataTables.h"
#include "Category.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace
{
	const std::vector<DoorData> Table = initializeDoorData();
}

Door::Door( const TextureHolder& textures, Type type)
: Entity(1)
, mType(type)
, mSprite(textures.get(Table[type].texture))
{
}

unsigned int Door::getCategory() const
{


	return Category::Door;
}


void Door::setPosition(const sf::Vector2f& position)
{

    mSprite.setPosition(position);

}
void Door::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

sf::FloatRect Door::getBoundingRect() const
{
	return mSprite.getGlobalBounds();
}


sf::Vector2f Door:: getSize()
{
   return    Table[mType].size;

}
