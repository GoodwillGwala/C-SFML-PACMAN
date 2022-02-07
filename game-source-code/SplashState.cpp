#include "SplashState.h"

#include "Utility.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>

SplashState::SplashState(GameStateMachine& machine, Context context)
:State{machine,context}
, mText()
, mShowText(true)
, mTextEffectTime(sf::Time::Zero)
{

	mBackgroundSprite.setTexture(context.textures->get(Textures::SplashScreen));

	mText.setFont(context.fonts->get(Fonts::Main));
	mText.setString("PRESS ANY KEY TO START");
	mText.setCharacterSize(30);

	mText.setPosition(sf::Vector2f(600,957));
}




bool SplashState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next state - Gameplay
	if (event.type == sf::Event::KeyReleased)
	{
		requestStackPop();
		requestStackPush(States::Game);
	}

	return true;
}

bool SplashState::update(sf::Time dt)
{
	mTextEffectTime += dt;

	if (mTextEffectTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}

	return true;
}
void SplashState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);
}
