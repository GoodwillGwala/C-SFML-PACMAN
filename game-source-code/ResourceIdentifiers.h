/**
*@class <ResourceIdentifiers>
*@brief This class provides information about different types of resources and their Identity
*/
#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H



namespace sf
{
	class Texture;
	class Font;
}
/**
∗ @namespace <Textures>
∗ @brief namespace to encapsulate textures
*
*/
namespace Textures
{

	/**
    ∗ @enum <ID>
    ∗ @brief enum to identify different texture resources
    *
    */
	enum ID
	{

		Blinky,
		Inky,
		Pinky,
		Ghosty,
		Clyde,
		Pacman,

		SplashScreen,
		Background,

		Wall,
		Door,

		Food,
		Food2,
		Food3,

		Key,

		Pallet,
		Pallet2,

		SuperPallet,
		Super2,
		Super3,
	};
}

/**
∗ @namespace <Textures>
∗ @brief namespace to encapsulate fonts
*
*/
namespace Fonts
{
	/**
    ∗ @enum <ID>
    ∗ @brief enum to identify different font resources
    *
    */
	enum ID
	{
		Main,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;

#endif
