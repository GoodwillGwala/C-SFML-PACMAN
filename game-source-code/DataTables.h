/**
∗ @class <DataTables>
∗ @brief This class facilitates the central data management system.
*
* This class stores data about object characteristics
* This allows data to be efficiently collected and accessed from a database
* This is the Data Layer
*
*/
#ifndef DATATABLES_H
#define DATATABLES_H

#include "ResourceIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <functional>
#include <memory>



class GameObject;
class Maze;

/**
∗ @struct <GameObjectData>
∗ @brief Database for GameObjects
*
* This struct stores data about game object characteristics
*/
struct GameObjectData
{
	int								Health;
	float							speed;
	Textures::ID					texture;
};



/**
∗ @struct <PickupData>
∗ @brief Database for Game Pickups
*
* This struct stores data about game pickup characteristics
*
*
*
*/
struct PickupData
{
	std::function<void(GameObject&)>	    eat;
	std::function<void(GameObject&)>	    godMode;
	std::function<void(GameObject&)>	    superMode;
	Textures::ID					        texture;
};
/**
∗ @struct <TileData>
∗ @brief Database for Game Tiles
*
* This struct stores data about game pickup characteristics
*
*
*
*/
struct TileData
{

    sf::Vector2f                            size;
    Textures::ID                            texture;
    sf::Color                               color;

};
/**
∗ @struct <DoorData>
∗ @brief Database for Game Doors / movable tiles
*
* This struct stores data about game access tile characteristics
*
*
*
*/
struct DoorData
{

    sf::Vector2f                            size;

    Textures::ID                            texture;

    sf::Color                               color;

};
/**
∗ @fn <initializeGameObjectData>
∗ @brief function to Initialise Game Object Data
* @return vector of structs
*
* The structs are information about a particular Game Object
*
*
*/
std::vector<GameObjectData>	                                    initializeGameObjectData();
/**
∗ @fn <initializeGameObjectData>
∗ @brief function to Initialise Game Object Data
* @return vector of structs
*
* The structs are information about a particular Game Object
*
*
*/
std::vector<PickupData>		                                    initializePickupData();
/**
∗ @fn <initializePickupData>
∗ @brief function to Initialise Pickup Object Data
* @return vector of structs
*
* The structs are information about a particular pickup object
*
*
*/
std::vector<TileData>                                           initializeTileData();
/**
∗ @fn <initializeTileData>
∗ @brief function to Initialise Tile object Data
* @return vector of structs
*
* The structs are information about a Tile object
*
*
*/
std::vector<DoorData>                                           initializeDoorData();
#endif
