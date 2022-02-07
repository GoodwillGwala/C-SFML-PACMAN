/**
*@class <Player>
*@brief This class provides the interface for controlling the player Game Object
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Command.h"

#include <SFML/Window/Event.hpp>

#include <map>


class CommandQueue;

class Player
{
	public:
		/**
        ∗ @enum <Action>
        ∗ @brief enum to identify different movement types of player object
        */
		enum Action
		{
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			ActionCount
		};
        /**
        ∗ @enum <MissionStatus>
        ∗ @brief enum to identify different player mission status
        *
        */
		enum MissionStatus
		{
			MissionRunning,
			MissionSuccess,
			MissionFailure
		};


	public:

		/**
        * @brief Constructor
        *
        */
								Player();

        /**
        * @brief function that provides the interface for handling local events
        * @param event object and Command Queue
        */
		void					handleEvent(const sf::Event& event, CommandQueue& commands);
        /**
        * @brief function that sets the player mission status
        * @param status
        *
        */


		void 					setMissionStatus(MissionStatus status);
		/**
        * @brief function that provides information about the player mission status
        * @param status
        *
        */

		MissionStatus 			getMissionStatus() const;

	private:
		void					initializeActions();



	private:
		std::map<sf::Keyboard::Key, Action>		mKeyBinding;
		std::map<Action, Command>				mActionBinding;
		MissionStatus 							mCurrentMissionStatus;
};

#endif
