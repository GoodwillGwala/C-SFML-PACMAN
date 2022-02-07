#include "World.h"
#include "Tile.h"
#include "Door.h"
#include "Pickup.h"
#include "Foreach.h"
#include "TextNode.h"
#include "Utility.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <memory>
#include <vector>

#include <limits>
#include <iostream>

using namespace std;

World::World(sf::RenderWindow& window, FontHolder& fonts)
: mWindow(window)
, mFonts(fonts)
, mTextures()
, mSceneGraph()
, mSceneLayers()
, mPlayerGameObject(nullptr)
, mEnemySpawnPoints()
, mActiveDoors()
, mHealthDisplay(nullptr)
, mScoreDisplay(nullptr)
, mStatsDisplay(nullptr)
, mHasEdibles(true)
{
	loadTextures();
	buildScene();

}

void World::update(sf::Time dt)
{

	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	handleCollisions();
    stateUpdate();
	updateTexts();


	mSceneGraph.removeWrecks();

	spawnEnemies();

	mSceneGraph.update(dt, mCommandQueue);



}

void World::draw()
{

	mWindow.draw(mSceneGraph);

}

void World::updateTexts()
{

    mScoreDisplay->setString(toString("SCORE :"+ toString(mPlayerGameObject->getScore())));
    mScoreDisplay->setPosition(1300, 100);


    mHealthDisplay->setString(toString("LIVES :"+ toString(mPlayerGameObject->getHealth())));
    mHealthDisplay->setPosition(1300,  300);

    auto edibles = mMaze->Pickupcount() - mPlayerGameObject->pickupcount();
    mStatsDisplay->setString(toString("EDIBLES LEFT:"+ toString(edibles)));
    mStatsDisplay->setPosition(1300,  500);



}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

Maze& World::getMaze()
{
	return *mMaze;
}

GameObject& World::getPlayer()
{
	return *mPlayerGameObject;
}

bool World::hasAlivePlayer() const
{
	return !mPlayerGameObject->isMarkedForRemoval();
}

bool World::hasEdibles() const
{


    if ( mMaze->Pickupcount() == mPlayerGameObject->pickupcount() )
    return !mHasEdibles;

    return mHasEdibles;

}

void World::loadTextures()
{


	mTextures.load(Textures::Wall, "resources/textures/Tile.png");
	mTextures.load(Textures::Door, "resources/textures/Door.png");
	mTextures.load(Textures::Pacman, "resources/textures/Pacman.png");

	mTextures.load(Textures::Food,  "resources/textures/food1.png");
	mTextures.load(Textures::Food2, "resources/textures/food2.png");
	mTextures.load(Textures::Food3, "resources/textures/food3.png");

	mTextures.load(Textures::Key,   "resources/textures/Key.png");

	mTextures.load(Textures::Pallet,   "resources/textures/pallet1.png");

	mTextures.load(Textures::SuperPallet,   "resources/textures/Super1.png");

	mTextures.load(Textures::Blinky,   "resources/textures/Blinky.png");
	mTextures.load(Textures::Inky,   "resources/textures/Inky.png");
	mTextures.load(Textures::Ghosty,   "resources/textures/Ghosty.png");
	mTextures.load(Textures::Pinky,   "resources/textures/Pinky.png");
	mTextures.load(Textures::Clyde,   "resources/textures/Clyde.png");

}

bool matchesCategories(Component::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

// Make sure first pair entry has category type1 and second has type2 using bit wise & operation
// This facilitates casting the right object for resolving the collisions
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}



void World::respawn(GameObject& object)
{

    if (object.getCategory() & Category::EnemyGameObject)
    {
        object.setPosition(mMaze->enemySpawn());
    }
    else{  object.setPosition(mMaze->playerSpawn());}

}

void World::handleCollisions()
{
	std::set<Component::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

	FOREACH(Component::Pair pair, collisionPairs)
	{
//-------------------------Player vs Enemy Collision Handling-------------------------

//		NormalPac is destroyed by normal Ghost ✅️
		if (matchesCategories(pair, Category::NormalPac, Category::NormalGhost))
		{
			auto& player = static_cast<GameObject&>(*pair.first);

			player.setPosition(player.getPreviousPosition());

            respawn(player);
			player.setVelocity(sf::Vector2f(0.f,0.f));
			player.damage();
		}

//		SuperPac destroys ScaredGhosts ✅️
		else if (matchesCategories(pair, Category::SuperPac, Category::ScaredGhost))
		{

			auto& ghost = static_cast<GameObject&>(*pair.second);


			ghost.setPosition(ghost.getPreviousPosition());

            respawn(ghost);
		}


        else if (matchesCategories(pair, Category::GodPac, Category::ScaredGhost))
		{


			auto& ghost = static_cast<GameObject&>(*pair.second);
            std::cout<<ghost.getCategory()<<std::endl;

			ghost.setPosition(ghost.getPreviousPosition());

            respawn(ghost);
		}



//-------------------------Player vs Pickup Collision Handling-------------------------

//		Player picks up food  ✅️
		if (matchesCategories(pair, Category::PlayerGameObject, Category::Food))
		{
			auto& player = static_cast<GameObject&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);


			pickup.apply(player, Category::Food);

			pickup.destroy();
		}
//		Player picks up SuperPallet  ✅️
		if (matchesCategories(pair, Category::PlayerGameObject, Category::SuperPallet))
		{
			auto& player = static_cast<GameObject&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);
			pickup.apply(player, Category::SuperPallet);
            squishGhosts();
			pickup.destroy();
			player.reward(50);
		}
//		Player picks up PowerPallet  ✅️
		if (matchesCategories(pair, Category::PlayerGameObject, Category::PowerPallet))
		{

			auto& player = static_cast<GameObject&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);


			pickup.apply(player, Category::PowerPallet);
			player.reward(50);
			scareGhosts();
			pickup.destroy();
		}

//        all player states can pick up key and open doors ✅️
		else if (matchesCategories(pair, Category::PlayerGameObject, Category::Key))
		{

			auto& pickup = static_cast<Pickup&>(*pair.second);
			checkOpenDoors(pickup);

		}


//-------------------------Objects vs Tile Collision Handling-------------------------


//		All game objects collide with walls ✅️
		else if (matchesCategories(pair, Category::GameObject, Category::Wall))
		{
			auto& object = static_cast<GameObject&>(*pair.first);
	        object.setPosition(object.getPreviousPosition());
	        object.setVelocity(sf::Vector2f(0.f,0.f));
	        if (object.getCategory() & Category::EnemyGameObject)
             object.hasCollided(true);

		}

        else if (matchesCategories(pair,Category::GodPac , Category::Door ))
		{
			auto& door = static_cast<Door&>(*pair.second);
			auto& object = static_cast<GameObject&>(*pair.first);
			std::cout<<object.getCategory()<<std::endl;
			door.destroy();

		}

		else if (matchesCategories(pair, Category::EnemyGameObject, Category::Tile)
			  || matchesCategories(pair, Category::SubNormalPac, Category::Tile))
		{


			auto& object = static_cast<GameObject&>(*pair.first);


	        object.setPosition(object.getPreviousPosition());



	        object.setVelocity(sf::Vector2f(0.f,0.f));


            if (object.getCategory() & Category::EnemyGameObject)
             object.hasCollided(true);

		}

	}


}

void World::buildScene()
{

    for (std::size_t i = 0; i < LayerCount; ++i)
	{
		Category::Type category = (i == Air) ? Category::SceneAirLayer : Category::None;

		Component::Ptr layer(new Component(category));
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));


	}

    std::unique_ptr<Maze> maze(new Maze(mTextures));
	mMaze = maze.get();
	mSceneLayers[Tile]->attachChild(std::move(maze));

//
	// Add player's GameObject
	std::unique_ptr<GameObject> player(new GameObject(GameObject::Pacman, mTextures, mFonts));
	mPlayerGameObject = player.get();
	mPlayerGameObject->setPosition(mMaze->playerSpawn());
	mSceneLayers[Tile]->attachChild(std::move(player));

	// Add player's health

	std::unique_ptr<TextNode> healthDisplay(new TextNode(mFonts, ""));

	mHealthDisplay = healthDisplay.get();
	mHealthDisplay->setCharacterSize(40);
	mHealthDisplay->setColor(sf::Color::Cyan);
	mSceneLayers[Air]->attachChild(std::move(healthDisplay));

    // Add player's Score

    std::unique_ptr<TextNode> scoreDisplay(new TextNode(mFonts, ""));
	mScoreDisplay = scoreDisplay.get();
	mScoreDisplay->setCharacterSize(40);
	mScoreDisplay->setColor(sf::Color::Cyan);
	mSceneLayers[Air]->attachChild(std::move(scoreDisplay));


//      Add Game Stats
    std::unique_ptr<TextNode> statsDisplay(new TextNode(mFonts, ""));
	mStatsDisplay = statsDisplay.get();
	mStatsDisplay->setCharacterSize(40);
	mStatsDisplay->setColor(sf::Color::Cyan);
	mSceneLayers[Air]->attachChild(std::move(statsDisplay));

	addEnemies();


}


void World::addEnemies()
{
//	 Add enemies to the spawn point container
	addEnemy(GameObject::Blinky,0.f,  0.f);
	addEnemy(GameObject::Inky,  0.f, -0.f);
	addEnemy(GameObject::Pinky, 0.f, -0.f);
	addEnemy(GameObject::Clyde, 0.f, -0.f);
}

void World::addEnemy(GameObject::Type type, float relX, float relY)
{
	SpawnPoint spawn(type, mMaze->enemySpawn().x + relX , mMaze->enemySpawn().y - relY);
	mEnemySpawnPoints.push_back(spawn);
}

void World::spawnEnemies()
{

	while (!mEnemySpawnPoints.empty() )
	{
		SpawnPoint spawn = mEnemySpawnPoints.back();
		std::unique_ptr<GameObject> enemy(new GameObject(spawn.type, mTextures, mFonts));
		enemy->setPosition(spawn.x, spawn.y);
		mSceneLayers[Tile]->attachChild(std::move(enemy));
		mEnemySpawnPoints.pop_back();
	}
}



void World::scareGhosts()
{

      Command scare;
	  scare.category = Category::EnemyGameObject;
	  scare.action = derivedAction<GameObject>([this] (GameObject& ghost, sf::Time)
	  {
	        if(!ghost.isDestroyed())
			{
			    ghost.setState(Category::ScaredGhost);
			    ghost.setColor(sf::Color::Blue);
			}

      });

      mCommandQueue.push(scare);


}


void World::stateUpdate()
{

      if(mPlayerGameObject->getCategory() == Category::Type::NormalPac)
      {
	    Command normal;
	    normal.category = Category::EnemyGameObject;
	    normal.action = derivedAction<GameObject>([this] (GameObject& ghost, sf::Time)
	    {
			if(!ghost.isDestroyed())

			ghost.setState(Category::Type::NormalGhost);
			ghost.setColor(sf::Color::White);
			ghost.setSize(1,1);

        });

        mCommandQueue.push(normal);

    }

}

void World::squishGhosts() //I'm tired can't think of a beter name 😴️
{
    Command squish;
	squish.category = Category::EnemyGameObject;
	squish.action   = derivedAction<GameObject>([this] (GameObject& ghost, sf::Time)
	{
	   if(!ghost.isDestroyed())
	   ghost.setState(GameObject::State::SquishedGhost);
	   ghost.setSize(0.5,0.5);


    });

    mCommandQueue.push(squish);
}

void World::checkOpenDoors(Pickup& key)
{
//    collect all doors and check for closes door to key
      if(key.isDestroyed()) return;

	  Command doorCollector;
	  doorCollector.category = Category::Door;
	  doorCollector.action   = derivedAction<Entity>([this] (Entity& door, sf::Time)
	  {

			if(!door.isDestroyed())
			{
			    mActiveDoors.push_back(&door);

            }
      });


      float minDistance = std::numeric_limits<float>::max();
	  Entity* closestDoor = nullptr;


      FOREACH(Entity* door, mActiveDoors)
	  {
	        float Distance = distance(*door, key);
            if (Distance < minDistance)
	        {
	    	    closestDoor = door;
	    	    minDistance = Distance;
	        }
      }

      if (closestDoor)
      {

          closestDoor->destroy();
          key.destroy();

      }

	mCommandQueue.push(doorCollector);
	mActiveDoors.clear();
}


TextureHolder& World::getTextures()
{

    return mTextures;

}

FontHolder& World::getFonts()
{
    return mFonts;

}
