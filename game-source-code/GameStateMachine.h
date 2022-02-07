/**
*@class <GameStateMachine>
*@brief This class is provides the interface for managing game states.
*
*This class manages the addition, removal and sequential accesing of states
*/
#ifndef GameStateMachine_H
#define GameStateMachine_H

#include "State.h"
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

#include <vector>
#include <utility>
#include <functional>
#include <map>


namespace sf
{
	class Event;
	class RenderWindow;
	class Time;
}

class GameStateMachine
{
	public:
        /**
        ∗ @brief  enum for identifying different actions performed on the state stack
        ∗
        */
		enum Action
		{
			Push,
			Pop,
			Clear,
		};


	public:

		/**
        * @brief Constructor
        * @param context
        *
        */
		                        explicit GameStateMachine(State::Context context);

        GameStateMachine ( const GameStateMachine& ) = delete;
	    GameStateMachine& operator= ( const GameStateMachine& ) = delete;

		/**
        * @brief function that provides the interface for registering a state based on a state identification.
        All states are registered to ensure that the memory is allocated prior to running the game
        * @param State Identity
        *
        */
		template <typename T>
		void                    registerState(States::ID stateID);

		/**
        * @brief function that facilitates the updating of states
        * @param time delta
        *
        */
		void                    update(sf::Time dt);
		/**
        *@brief function that facilitates the drawing of states
        */
		void                    draw();
		/**
        * @brief function that facilitates event handling
        * @param event
        */
		void                    handleEvent(const sf::Event& event);
        /**
        ∗ @brief  function that facilitates the inserting a new state in the state stack
        ∗ @param event
        */
		void                    pushState(States::ID stateID);
		/**
        ∗ @brief  function that facilitates the accessing and removal of a state from the state stack
        ∗
        */
		void                    popState();
		/**
        ∗ @brief  function that facilitates the removing of  all states from the state stack
        ∗
        */
		void                    clearStates();
        /**
        ∗ @brief  function queries if the state stack is empty
        ∗ @return boolean flag
        */
		bool                    isEmpty() const;


	private:
	    /**
        * @brief function that facilitates the creation of a state
        * @param States::ID
        * @return unique pointer to the state
        */
		State::Ptr              createState(States::ID stateID);
		/**
        * @brief function that facilitates the updating of the state stack
        */
		void                    applyPendingChanges();


	private:

        /**
        *@struct <PendingChange>
        *@brief This struct provides the facilitation of updating the game state stack
        */
		struct PendingChange
		{
			/**
            * @brief Constructor
            * @param Action StateID
            *
            */
			explicit            PendingChange(Action action, States::ID stateID = States::None);

			Action	            action;
			States::ID	        stateID;
		};


	private:

		std::vector<State::Ptr>	                            mStack;
		std::vector<PendingChange>	                        mPendingList;

		State::Context										mContext;
		std::map<States::ID, std::function<State::Ptr()>>	mFactories;
};


template <typename T>
void GameStateMachine::registerState(States::ID stateID)
{
	mFactories[stateID] = [this] ()
	{
		return State::Ptr(new T(*this, mContext));
	};
}

#endif
