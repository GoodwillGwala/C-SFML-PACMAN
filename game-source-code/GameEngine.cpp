#include "GameEngine.h"
#include "Utility.h"
#include "State.h"
#include "StateIdentifiers.h"
#include "SplashState.h"
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"

//static declarations
float GameEngine::SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;
float GameEngine::SCREEN_WIDTH  = sf::VideoMode::getDesktopMode().width;
const sf::Time GameEngine::TimePerFrame = sf::seconds(1.f/60.f);

GameEngine::GameEngine()
: mWindow{sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,60),"SUPER-PAC MAN!"}
, mTextures()
, mFonts()
, mPlayer()
, mGameStateMachine(State::Context(mWindow, mTextures, mFonts, mPlayer))
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);

	mFonts.load(Fonts::Main,"resources/fonts/emulogic.ttf");

	mTextures.load(Textures::SplashScreen,"resources/textures/SplashScreen.png");

	registerStates();
	mGameStateMachine.pushState(States::Splash);
}

void GameEngine::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		if (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			if (mGameStateMachine.isEmpty())
				mWindow.close();
		}


		render();
	}
}

void GameEngine::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mGameStateMachine.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void GameEngine::update(sf::Time dt)
{
	mGameStateMachine.update(dt);
}

void GameEngine::render()
{
	mWindow.clear();

	mGameStateMachine.draw();


	mWindow.display();
}



void GameEngine::registerStates()
{
	mGameStateMachine.registerState<SplashState>(States::Splash);
	mGameStateMachine.registerState<GameState>(States::Game);
	mGameStateMachine.registerState<PauseState>(States::Pause);
	mGameStateMachine.registerState<GameOverState>(States::GameOver);
}

sf::RenderWindow&  GameEngine::getWindow()
{
    return mWindow;

}

TextureHolder& GameEngine::getTextures()
{

    return mTextures;

}

FontHolder& GameEngine::getFonts()
{
    return mFonts;

}

GameStateMachine& GameEngine::getStateMachine()
{
    return mGameStateMachine;
}
