/**
*@class <SplashState>
*@brief This class provides the interface for the Splash screen
*/
#ifndef SplashState_H
#define SplashState_H

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class SplashState : public State
{
	public:

		/**
        * @brief Constructor
        * @param State Machine and Context
        *
        */

							SplashState(GameStateMachine& stack, Context context);
        /**
        * @brief function that renders drawable objects
        */
		virtual void		draw();
		/**
        * @brief function that updates class state
        * @param Update time interval
        * @return flag whether more updates need to made at upper level
        *
        */
		virtual bool		update(sf::Time dt);
		/**
        * @brief function that provides the interface for handling local events
        * @param event object
        * @return flag whether more events need to be handles at upper level
        */
		virtual bool		handleEvent(const sf::Event& event);


	private:
		sf::Sprite			mBackgroundSprite;
		sf::Text			mText;

		sf::RectangleShape  mFader;
		sf::Color           mAlpha;

		bool				mShowText;
		sf::Time			mTextEffectTime;
		sf::Texture         mTexture;
};

#endif
