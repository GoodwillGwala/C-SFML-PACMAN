/**
∗ @class <Command>
∗ @brief This class provides the interface for creating a command and applying the command to an object
*/
#ifndef COMMAND_H
#define COMMAND_H

#include "Category.h"

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

//forward declare.
class Component;

/**
∗ @struct <Command>
∗ @brief This struct provides the interface for creating a command
*/
struct Command
{
	typedef std::function<void(Component&, sf::Time)> Action;

								Command();

	Action						action;
	unsigned int				category;
};
/**
∗ @brief function provides the interface for applying a command to a derived object
*/
template <typename GameObject, typename Function>
Command::Action derivedAction(Function function)
{
	return [=] (Component& node, sf::Time dt)
	{

		assert(dynamic_cast<GameObject*>(&node) != nullptr);


		function(static_cast<GameObject&>(node), dt);
	};
}

#endif
