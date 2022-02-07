/**
*@brief This header provides the definition of utility functions utilised by game objects
*/
#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <sstream>


namespace sf
{
	class Sprite;
	class Text;
}

/**
*@brief Template function to convert object to string
*this caters for enums, integral types etc
*@param object which is convertable to string
*@return object as a string
*
*/
template <typename T>
std::string		toString(const T& value);

/**
*@brief function to center sprite's position i.e sprites position is defined by it's center
*@param SFML sprite
*/
void			centerOrigin(sf::Sprite& sprite);
/**
*@brief function to center text's position i.e text position is defined by it's center
*@param SFML text
*/
void			centerOrigin(sf::Text& text);
/**
*@brief function that facilitates random number generation using a random engine
*@param range of random number described by the exclusive max and inclusive minimum
*By default the minimum is zero
*/

int				randomInt(int exclusiveMax, int inclusiveMin=0);
/**
*@brief function that facilitates the calculation of the length of a vector
*@param vector of floats
*@return length as a float
*/
float			length(sf::Vector2f vector);

#include "Utility.inl"
#endif
