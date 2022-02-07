#include "Maze.h"
#include "DataTables.h"
#include "Utility.h"
#include "Tile.h"
#include "Door.h"
#include "Pickup.h"
#include <iostream>
#include "ResourceHolder.h"
#include <algorithm>

Maze::Maze(const TextureHolder& textures)
: mCount(0)
{



int map [] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,4,8,5,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,8,4,1,
    1,0,1,3,1,0,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,0,1,3,1,0,1,
    1,5,1,2,1,0,3,2,0,2,0,2,0,2,0,2,0,2,0,2,3,0,1,2,1,0,1,
    1,0,1,3,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,3,1,0,1,
    1,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,4,1,
    1,8,1,3,1,0,0,0,1,0,1,0,1,3,1,1,1,0,1,0,0,0,1,3,1,0,1,
    1,0,1,2,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,2,1,0,1,
    1,0,1,3,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,3,1,0,1,
    1,0,8,0,8,0,0,0,1,0,0,7,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
    1,0,1,3,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,3,1,4,1,
    1,0,1,2,2,2,1,0,1,0,0,0,0,8,0,0,0,0,1,0,1,2,2,2,1,0,1,
    1,0,1,3,1,2,1,0,1,5,0,0,0,8,0,0,0,5,1,0,1,2,1,3,1,0,1,
    1,0,0,0,3,2,3,0,1,1,1,1,1,1,1,1,1,1,1,0,3,2,3,0,0,0,1,
    1,0,0,0,1,1,1,8,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
    1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,5,0,0,0,0,0,1,
    1,0,1,3,1,0,0,4,1,0,1,0,0,6,0,0,1,0,1,4,0,0,1,3,1,0,1,
    1,0,1,2,1,0,1,3,1,1,1,0,0,0,0,0,1,1,1,3,1,0,1,2,1,4,1,
    1,0,1,2,1,8,1,0,0,3,0,8,0,4,0,0,0,3,0,0,1,0,1,2,1,0,1,
    1,0,1,3,1,0,1,0,1,1,0,0,1,1,1,0,0,1,1,0,1,0,1,3,1,0,1,
    1,0,0,4,0,4,1,0,1,5,0,0,1,2,1,0,0,0,1,0,1,0,0,0,0,0,1,
    1,4,1,3,1,0,1,3,1,0,0,0,1,3,1,0,0,0,1,3,1,0,1,3,1,4,1,
    1,0,1,2,1,4,0,0,0,0,0,0,0,8,0,0,0,8,0,0,0,4,1,2,1,0,1,
    1,0,1,3,1,0,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,0,1,3,1,0,1,
    1,4,5,0,0,8,3,2,0,2,0,2,5,2,0,2,0,2,0,2,3,0,8,0,0,4,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

};




    auto width = 27;
    auto height = 26;
    auto tileSize = sf::Vector2u(40,40);



    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            sf::Vector2f position = sf::Vector2f((i*tileSize.x), (j*tileSize.y ));

            int tileNumber = map[i + j * width];
            switch(tileNumber)
            {


                case 1:
                walls.push_back(position);
                break;

                case 2:
                food.push_back(position);
                mCount++;
                break;

                case 3:
                doors.push_back(position);
                break;

                case 4:
                keys.push_back(position);
                break;

                case 5:
                superpallets.push_back(position);

                mCount++;
                break;

                case 6:
                playerSpawnPosition = position;
                break;

                case 7:
                enemySpawnPosition = position;
                break;

                case 8:
                powerpallets.push_back(position);
                mCount++;
                break;
                default:
                break;
            }



        }



         std::for_each(std::begin(walls), std::end(walls), [&](auto position)
        {
            std::unique_ptr<Tile> tile(new Tile(textures));
            tile->setPosition(position);
            attachChild(std::move(tile));


        });

        std::for_each(std::begin(doors), std::end(doors), [&](auto position)
        {
            std::unique_ptr<Door> door(new Door(textures));
            door->setPosition(position);
            attachChild(std::move(door));


        });



        std::for_each(std::begin(food), std::end(food), [&](auto position)
        {
            std::unique_ptr<Pickup> pickup(new Pickup(textures,static_cast<Pickup::Type>(randomInt(3))));
            pickup->setPosition(position);
            attachChild(std::move(pickup));


        });

        std::for_each(std::begin(keys), std::end(keys), [&](auto position)
        {
            std::unique_ptr<Pickup> pickup(new Pickup(textures,static_cast<Pickup::Type>(3)));

            pickup->setPosition(position);
            attachChild(std::move(pickup));


        });

        std::for_each(std::begin(powerpallets), std::end(powerpallets), [&](auto position)
        {
            std::unique_ptr<Pickup> pickup(new Pickup(textures,static_cast<Pickup::Type>(4)));
            pickup->setPosition(position);
            attachChild(std::move(pickup));


        });

        std::for_each(std::begin(superpallets), std::end(superpallets), [&](auto position)
        {
            std::unique_ptr<Pickup> pickup(new Pickup(textures,static_cast<Pickup::Type>(6)));
            pickup->setPosition(position);
            attachChild(std::move(pickup));


        });


}


int Maze::Pickupcount()
{
    return mCount;

}

sf::Vector2f Maze::playerSpawn()
{
    return playerSpawnPosition;
}

sf::Vector2f Maze::enemySpawn()
{
    return enemySpawnPosition;

}
