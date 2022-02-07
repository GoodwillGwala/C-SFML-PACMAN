/**
*@class <PauseState>
*@brief This class provides the interface for pausing gameplay
*/
#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State
{
public:

	/**
    * @brief Constructor
    * @param State Machine and Context
    *
    */
						    PauseState(GameStateMachine& stack, Context context);

	/**
    * @brief function that renders drawable objects
    */
	virtual void		    draw() override;
	/**
    * @brief function that updates class state
    * @param Update time interval
    * @return flag whether more updates need to made at upper level
    *
    */
	virtual bool		    update(sf::Time dt) override;
	/**
    * @brief function that provides the interface for handling local events
    * @param event object
    * @return flag whether more events need to be handles at upper level
    */
	virtual bool		    handleEvent(const sf::Event& event) override;


private:
		sf::Sprite			mBackgroundSprite;
		sf::Text			mPausedText;

};

#endif
