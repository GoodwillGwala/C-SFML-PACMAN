/**
*@class <GameState>
*@brief This class provides the interface for the gameplay
*/
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "World.h"
#include "Player.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
	public:
	/**
    * @brief Constructor
    * @param State Machine and Context
    *
    */
							GameState(GameStateMachine& stack, Context context);
    private:
		virtual void		draw() override;
		virtual bool		update(sf::Time dt) override;
		virtual bool		handleEvent(const sf::Event& event) override;


	private:
		World				mWorld;
		Player&				mPlayer;
};

#endif
