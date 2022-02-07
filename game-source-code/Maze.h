/**
*@class <Maze>
*@brief This class is provides the interface creating and managing the game maze.
*
*This class manages the creation of the maze and it's content
*/
#ifndef MAZE_H
#define MAZE_H

#include "Component.h"
#include <vector>
#include "ResourceIdentifiers.h"
class Maze : public Component
{

public:



    /**
    * @brief Constructor
    * @param textures
    *
    */
                                Maze(const TextureHolder& textures);

    /**
    * @brief function that gives information about an empty tile
    * @return position vector
    */
 	sf::Vector2f                getEmptyTile();
 	/**
    * @brief function that gives information enemy spawn position
    * @return position vector
    */
    sf::Vector2f                enemySpawn();
    /**
    * @brief function that gives information player spawn position
    * @return position vector
    */
    sf::Vector2f                playerSpawn();
    /**
    * @brief function that gives information about amount of pickups in the maze
    * @return integer count
    */
    int                         Pickupcount();



private:

    std::vector<sf::Vector2f>   walls;
    std::vector<sf::Vector2f>   food;
    std::vector<sf::Vector2f>   empty;
    std::vector<sf::Vector2f>   doors;
    std::vector<sf::Vector2f>   keys;
    std::vector<sf::Vector2f>   powerpallets;
    std::vector<sf::Vector2f>   superpallets;

    sf::Vector2f                playerSpawnPosition;
    sf::Vector2f                enemySpawnPosition;
    int                         mCount;



};

#endif
