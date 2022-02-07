/**
∗ @class <GameObject>
∗ @brief This class models a Game Object that is represented in the game world.
* It also models it's basic characteristics and responsibilities.
* This class inherits from Class Entity
*/
#ifndef GameObject_H
#define GameObject_H

#include "Entity.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>

// Foward declarations
namespace sf
{

    class Color;

}
class CommandQueue;

class GameObject : public Entity
{
public:

        /**
        ∗ @brief  enum for identifying different types of game objects
        ∗
        */
		enum Type
		{
			Pacman,
			Blinky,
			Inky,
			Pinky,
			Clyde,
			Ghosty,
			TypeCount
		};

        /**
        ∗ @brief  enum for identifying different game objects states.
        ∗ The states are represented as binary bits.
        * Binary operations are used to combine different States.
        */
		enum State
		{
		    NormalPac           = 1 << 1,
		    SuperPac            = 1 << 2,
            GodPac              = 1 << 3,
		    NormalGhost         = 1 << 4,
		    ScaredGhost         = 1 << 5,
		    SquishedGhost       = 1 << 6,

		    SuperNormalPac      = SuperPac    ^ GodPac,
		    SuperNormalEnemy    = ScaredGhost ^ SquishedGhost,

		    StateCount
		};




public:
        /**
        * @brief Constructor
        * @param type of object, textures and fonts
        *
        */

			explicit					GameObject(Type type, const TextureHolder& textures, const FontHolder& fonts);

        /**
        * @brief function that facilitates the querying of a game objects category.
        * The category of a game object depends on the state that it is in.
        * @return Category
        */
        virtual unsigned int	getCategory() const override;
        /**
        * @brief function that facilitates the querying whether an object should be removed.
        * @return flag, true to remove false otherwise.
        */
        virtual bool 			isMarkedForRemoval() const override;
		/**
        ∗ @brief  function that provides information about the previous position.
        * @return vector position.
        */
		sf::Vector2f            getPreviousPosition() const;
		/**
        ∗ @brief  function that retrieves game object maximum speed from data layer.
        ∗ @return float speed from data table.
        */
		float					getMaxSpeed() const;
		/**
        ∗ @brief  Provides interface for setting an objects state
        * @param enumeration binary state.
        */
        void                    setState(unsigned int state);
        /**
        ∗ @brief  Provides interface for informing a the world that the object has collided.
        * @param flag, true if collided false otherwise.
        */
        void                    hasCollided(bool collided);
        /**
        ∗ @brief  Provides interface for changing Game Object color.
        * @param  SFML color.
        */
        void                    setColor(sf::Color color);
        /**
        ∗ @brief  Provides interface for changing Game Object size.
        * @param  size dimensions as floats.
        */
        void                    setSize(float x, float y);
private:
		/**
        ∗ @brief  function that determines whether Game Object is a player
        ∗ @return boolean , true or false
        */
		bool					isPlayer() const;
		/**
        ∗ @brief  function to executes state change
        */
        void                    checkStateChange();
		/**
        ∗ @brief  Provides interface for retrieving Game Object State
        * @return unsigned int corresponding to State enum
        */
        unsigned int            currentState();
        /**
        ∗ @brief  Provides interface for updating autonomous object movement patterns
        * @param Time per Frame
        */
		void					updateMovementPattern(sf::Time dt);

		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void 			updateCurrent(sf::Time dt, CommandQueue& commands) override;
		virtual sf::FloatRect	getBoundingRect() const override;




private:

		Type					mType;
		State                   mCurrentState;
		sf::Time                mGodStateCount;
		sf::Time                mStateCountdown;
        sf::Vector2f            mPreviousPosition;
		sf::Sprite				mSprite;

		bool                    mGodStateActive;
		bool                    mSuperStateActive;
        bool                    mCollided;
        bool                    mIsMarkedForRemoval;
};

#endif
