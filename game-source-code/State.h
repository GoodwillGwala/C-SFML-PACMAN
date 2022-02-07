/**
*@class <State>
*@brief This class is provides the interface for states. All  states inherit from this class
*
*/
#ifndef STATE_H
#define STATE_H

#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf
{
	class RenderWindow;
}

class GameStateMachine;
class Player;

class State
{
public:

typedef std::unique_ptr<State> Ptr;

public:



    /**
    *@class <Context>
    *@brief This struct provides the interface for the context of the game. The context contains game resources and a player controller object
    *
    */
    struct Context
	{
			/**
            *@brief Constructor
            *@param window , textures , fonts and player controller object
            *
            */
			Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);

			sf::RenderWindow*	window;
			TextureHolder*		textures;
			FontHolder*			fonts;
			Player*				player;
	};

public:
    /**
    *@brief Constructor
    *@param state machine, context
    */
	State(GameStateMachine& machine, Context context );
	virtual ~State();

	State ( const State& ) = delete;
	State& operator= ( const State& ) = delete;



public:
	/**
    ∗ @brief  function that provides the interface for updating states
    ∗
    */

	virtual bool update(sf::Time dt ) = 0;
	/**
    ∗ @brief  function that provides the interface for drawing states
    ∗
    */
	virtual void draw() = 0;
    /**
    ∗ @brief  function that provides the interface for handling state events
    ∗
    */
    virtual bool handleEvent(const sf::Event& event) = 0;




protected:

    /**
    ∗ @brief  function that provides the interface for instantiating a new state in the stack
    ∗
    */
    void requestStackPush(States::ID stateID);
    /**
    ∗ @brief  function that provides the interface for removing a state
    ∗
    */
	void requestStackPop();
	/**
    ∗ @brief  function that provides the interface for clearing the stack
    ∗
    */
	void requestStateClear();

    /**
    ∗ @brief  function that provides the context for a state
    ∗
    */
    Context getContext() const;


private:
    Context mContext;
    GameStateMachine* m_machine;



};

#endif
