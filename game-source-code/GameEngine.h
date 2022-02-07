/**
∗ @class <GameEngine>
∗ @brief This class provides the interface for the game loop, state instatiation and state executions
*/

#ifndef GameEngine_H
#define GameEngine_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Player.h"
#include "GameStateMachine.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>




class GameEngine
{
	public:
		/**
        * @brief Constructor
        *
        */

								                      GameEngine();
        GameEngine ( const GameEngine& )              = delete;
	    GameEngine& operator= ( const GameEngine& )   = delete;
		/**
        ∗ @brief  Provides interface for executing the game loop.
        ∗
        */
		void					    run();
		/**
        ∗ @brief  Provides interface for retrieving the Render Window.
        ∗ @return SFML Render Window.
        */
		sf::RenderWindow&           getWindow();
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
        ∗ @brief  Provides interface for retrieving the State Machine.
        ∗ @return State Machine.
        */
		GameStateMachine&           getStateMachine();


private:

		/**
        ∗ @brief  Provides interface for processing all game inputs
        ∗
        */
		void					    processInput();
		/**
        ∗ @brief  Provides interface for updating the game loop in constant time intervals
        ∗ @param update time interval - time per frame
        */
		void					    update(sf::Time dt);
		/**
        ∗ @brief  Provides interface for rendering the game loop in constant time intervals
        ∗
        */

		void					    render();
		/**
        ∗ @brief  Provides interface for registering all game states
        ∗
        */

		void					    registerStates();



		static const sf::Time	    TimePerFrame;
	    static float                SCREEN_WIDTH;
	    static float                SCREEN_HEIGHT;

		sf::RenderWindow		    mWindow;
		TextureHolder			    mTextures;
	  	FontHolder				    mFonts;
		Player					    mPlayer;

		GameStateMachine	        mGameStateMachine;


};
#endif
