/**
*@class <GameOverState>
*@brief This class provides the interface for the post gameplay state
*/
#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "State.h"


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameOverState : public State
{
	public:

	    /**
        * @brief Constructor
        * @param State Machine and Context
        *
        */
							GameOverState(GameStateMachine& stack, Context context);




	private:

		virtual void		draw() override;
		virtual bool		update(sf::Time dt) override;
		virtual bool		handleEvent(const sf::Event& event) override;

		sf::Text			mGameOverText;
		sf::Time			mElapsedTime;
};

#endif
