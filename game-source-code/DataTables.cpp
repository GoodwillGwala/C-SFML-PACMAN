#include "DataTables.h"
#include "GameObject.h"
#include "Pickup.h"
#include "Tile.h"
#include "Door.h"
#include "Maze.h"

using namespace std::placeholders;

std::vector<GameObjectData> initializeGameObjectData()
{
	std::vector<GameObjectData> data(GameObject::TypeCount);

	data[GameObject::Pacman].Health = 3;
	data[GameObject::Pacman].speed = 400.f;

	data[GameObject::Pacman].texture = Textures::Pacman;




	data[GameObject::Blinky].Health = 1;
	data[GameObject::Blinky].speed = 2000.f;
	data[GameObject::Blinky].texture = Textures::Blinky;



	data[GameObject::Inky].Health = 1;
	data[GameObject::Inky].speed = 800.f;
	data[GameObject::Inky].texture = Textures::Inky;


    data[GameObject::Pinky].Health = 1;
	data[GameObject::Pinky].speed = 800.f;
	data[GameObject::Pinky].texture = Textures::Pinky;


	data[GameObject::Clyde].Health = 1;
	data[GameObject::Clyde].speed = 900.f;
	data[GameObject::Clyde].texture = Textures::Clyde;

	data[GameObject::Ghosty].Health = 1;
	data[GameObject::Ghosty].speed = 900.f;
	data[GameObject::Ghosty].texture = Textures::Ghosty;


	return data;
}

std::vector<TileData> initializeTileData()
{
    std::vector<TileData> data(Tile::TypeCount);


    data[Tile::Wall].color = sf::Color::Green;
    data[Tile::Wall].size = sf::Vector2f(40,40);
    data[Tile::Wall].texture = Textures::Wall;

    return data;

}

std::vector<DoorData> initializeDoorData()
{
	std::vector<DoorData> data(Door::TypeCount);


	data[Door::OneWay].texture = Textures::Door;


	return data;
}

std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);
//  FOOD
	data[Pickup::Food].texture          = Textures::Food;
	data[Pickup::Food].eat              = std::bind(&GameObject::reward, _1, 10);

	data[Pickup::Food2].texture         = Textures::Food2;
	data[Pickup::Food2].eat             = std::bind(&GameObject::reward, _1, 25);

    data[Pickup::Food3].texture         = Textures::Food3;
	data[Pickup::Food3].eat             = std::bind(&GameObject::reward, _1, 25);
//  KEY
	data[Pickup::Key].texture           = Textures::Key;

//  SUPER MODE

    data[Pickup::Pallet].texture        = Textures::Pallet;
	data[Pickup::Pallet].superMode      = std::bind(&GameObject::setState, _1, GameObject::State::SuperPac);
//  GOD MODE
    data[Pickup::SuperPallet].texture   = Textures::SuperPallet;
	data[Pickup::SuperPallet].godMode   = std::bind(&GameObject::setState, _1, GameObject::State::GodPac);




	return data;
}
