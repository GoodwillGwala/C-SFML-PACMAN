/**
∗ @class <CommandQueue>
∗ @brief This class facilitates the central communication system.
*
* This facilitates object conversation through a mediator.
* This also allows applying a command to multiple objects
*
*
*/

#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include "Command.h"

#include <queue>


class CommandQueue
{
	public:


		/**
		*@brief function to facilitate adding a command to the queue
		*@param Command
		*
		*/
		void						push(const Command& command);

		/**
		*@brief function to facilitate accessing a command from the queue
		*@return Command
		*
		*/
		Command						pop();
		/**
		*@brief function to query if command queue is empty
		*@return bool
		*
		*/
		bool						isEmpty() const;


	private:
		std::queue<Command>			mQueue;
};

#endif
