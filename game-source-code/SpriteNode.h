/**
*@class <SpriteNode>
*@brief This class provides the definition of a sprite node and it's responsibilities
*/
#ifndef BOOK_SPRITENODE_H
#define BOOK_SPRITENODE_H

#include "Component.h"

#include <SFML/Graphics/Sprite.hpp>


class SpriteNode : public Component
{
	public:

		/**
        * @brief Constructor
        * @param textures
        *
        */
		explicit			SpriteNode(const sf::Texture& texture);



	private:

		virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


	protected:
		sf::Sprite			mSprite;
};

#endif
