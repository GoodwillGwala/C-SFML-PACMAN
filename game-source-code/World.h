/**
∗ @class <World>
∗ @brief This class provides the implementation of the game World
*
* This class facilitates game object instantiation, communication and presentation
* This is the Presentation Layer
*
*
*/

#ifndef WORLD_H
#define WORLD_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Component.h"
#include "SpriteNode.h"
#include "GameObject.h"
#include "CommandQueue.h"
#include "Command.h"
#include "Maze.h"
#include "TextNode.h"



//Containers
//#include <map>
#include <array>
#include <queue>



namespace sf
{
	class RenderWindow;
	class Color;
}



class Entity;
class Pickup;


class World
{
	public:
		/**
        * @brief enumeration to present the different layers of the world
        *
        */
		enum Layer
		{
			Background,
			Tile,
			Air,
			LayerCount
		};
		/**
        * @brief struct to encapsulate information about Game Object spawn points based on type
        *
        */

		struct SpawnPoint
		{

			SpawnPoint(GameObject::Type type, float x, float y)
			: type(type)
			, x(x)
			, y(y)
			{
			}

			GameObject::Type type;
			float x;
			float y;
		};

	public:

		/**
        * @brief Constructor
        * @param sfml Render Window and Fonts
        *
        */
		explicit							World(sf::RenderWindow& window, FontHolder& fonts);
		World ( const World& )              = delete;
	    World& operator= ( const World& )   = delete;
		/**
        * @brief function to facilitate sequential call of update to game world objects and command dispatching
        * @param SFML update time interval
        */
		void								update(sf::Time dt);
		/**
        * @brief function to facilitate the rendering of drawable objects of node graphs to the Render Window
        */
		void								draw();
        /**
        * @brief function to retreive the command queue
        * @return Command queue
        */
		CommandQueue&						getCommandQueue();
		Maze&                               getMaze();
		GameObject&                         getPlayer();
		/**
        ∗ @brief  Provides interface for retrieving the textures.
        ∗ @return texture holder.
        */
		TextureHolder&	            getTextures();
		/**
        ∗ @brief  Provides interface for retrieving the fonts.
        ∗ @return texture holder.
        */
		FontHolder&                 getFonts();
		/**
        * @brief function to query if player is still alive
        * @return flag , true or false
        */

		bool 								hasAlivePlayer() const;
		/**
        * @brief function to query if world still has edible objects
        * Checks if player has won / cleared the level
        * @return flag , true or false
        */
		bool                                hasEdibles() const;

//      Doxygen ignores private variables
	private:
//		loads textures required during game play and post game play
		void								loadTextures();
//      resolves collisions based on object category
		void								handleCollisions();
//		Updates text to be presented on screen e.g score , lives etc
		void                                updateTexts();
//      constructs the world
		void								buildScene();
//      instantiates enemy objects
		void								addEnemies();
//		Adds instantiated enemy objects to their relative spawn positions
		void								addEnemy(GameObject::Type type, float relX, float relY);
//		Adds instantiated enemy objects to the world
		void								spawnEnemies();
//		respawn game objects
		void                                respawn(GameObject& object);
//		opens closest door to the key
        void                                checkOpenDoors(Pickup& key);
//      change presentation of scared ghost - Supa-pac Mode
        void                                scareGhosts();
//      change presentation of squished ghost - God-pac Mode
        void                                squishGhosts();
//      update state presentation of objects
        void                                stateUpdate();


		bool                                mHasEdibles;




		sf::RenderWindow&					mWindow;


		TextureHolder						mTextures;
		FontHolder&							mFonts;

		Component							mSceneGraph;

		std::array<Component*, LayerCount>	mSceneLayers;
		CommandQueue						mCommandQueue;


		sf::Vector2f						mSpawnPosition;

		GameObject*							mPlayerGameObject;

		std::vector<SpawnPoint>				mEnemySpawnPoints;

		std::vector<Entity*>                mActiveDoors;

		Maze*                               mMaze;
//      Text objects
        TextNode*				            mHealthDisplay;
		TextNode*				            mScoreDisplay;
		TextNode*                           mStatsDisplay;

};

#endif
