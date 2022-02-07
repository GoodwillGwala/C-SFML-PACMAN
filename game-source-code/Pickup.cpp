#include "Pickup.h"
#include "DataTables.h"
#include "Category.h"
#include "CommandQueue.h"
#include "Utility.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderTarget.hpp>


namespace
{
	const std::vector<PickupData> Table = initializePickupData();
}

Pickup::Pickup(const TextureHolder& textures, Type type )
: Entity(1)
, mType(type)
, mSprite(textures.get(Table[type].texture))
{

}

Pickup::Pickup()
:Entity(1)
,mType(Type::Food)
, mSprite()
{


}

unsigned int Pickup::getCategory() const
{


	if (mType == Type::Key)
	{

	    return Category::Key;
	}
	else if (mType == Type::SuperPallet)
	{
	    return Category::SuperPallet;

	}
	else if (mType == Type::Pallet)
	{
	    return Category::PowerPallet;

	}
	else return Category::Food;


}

sf::FloatRect Pickup::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Pickup::apply(GameObject& player, unsigned int category) const
{

    switch(category)
    {
        case Category::Food :
        Table[mType].eat(player);
        break;

        case Category::PowerPallet :
        Table[mType].superMode(player);
        break;

        case Category::SuperPallet :
        Table[mType].godMode(player);
        break;

        default:
        break;

    }

}


void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
