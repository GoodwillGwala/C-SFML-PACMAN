#include "TextNode.h"
#include "Utility.h"

#include <SFML/Graphics/RenderTarget.hpp>


TextNode::TextNode(const FontHolder& fonts, const std::string& text)
{
	mText.setFont(fonts.get(Fonts::Main));
	mText.setCharacterSize(20);
	setString(text);
}

void TextNode::setString(const std::string& text)
{
	mText.setString(text);

}

void TextNode::setCharacterSize(unsigned int size)
{

    mText.setCharacterSize(size);
}

void TextNode::setColor( const sf::Color color)
{
    mText.setFillColor(color);

}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mText, states);
}
