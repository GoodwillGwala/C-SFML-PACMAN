/**
*@class <TextNode>
*@brief This class provides the definition of a text node and it's responsibilities
*/
#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Component.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace sf
{

    class Color;

}

class TextNode : public Component
{
	public:

		/**
        * @brief Constructor
        * @param fonts and text string
        *
        */
		explicit			TextNode(const FontHolder& fonts, const std::string& text);
        /**
        * @brief function to set string to text
        * @param text string
        *
        */
		void				setString(const std::string& text);
		/**
        * @brief function to set text character size
        * @param character size
        *
        */
		void                setCharacterSize(unsigned int size);
		/**
        * @brief function to set text color
        * @param SFML color
        *
        */
		void                setColor(const sf::Color color);


	private:
		virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		sf::Text			mText;
};

#endif
