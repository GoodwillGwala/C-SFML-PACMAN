#include "GameObject.h"
#include "DataTables.h"
#include "Utility.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


namespace
{
	const std::vector<GameObjectData> Table = initializeGameObjectData();
}

GameObject::GameObject(Type type, const TextureHolder& textures, const FontHolder& fonts)
: Entity(Table[type].Health)
, mType(type)
, mIsMarkedForRemoval(false)
, mCollided(false)
, mStateCountdown(sf::Time::Zero)
, mGodStateCount(sf::Time::Zero)
, mSprite(textures.get(Table[type].texture))
{


	if(isPlayer() )
	{

	    mCurrentState = State::NormalPac;
    }
	else
	{
	    mCurrentState = State::NormalGhost;
	    setVelocity(0,-100);
	}

}

void GameObject::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void GameObject::updateCurrent(sf::Time dt, CommandQueue& commands)
{

	if (isDestroyed())
	{


		mIsMarkedForRemoval = true;
		return;
	}

    mPreviousPosition =	Entity::getPosition();

	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

	if(mGodStateActive || mSuperStateActive)
	checkStateChange();

	if( mStateCountdown > sf::Time::Zero)
	mStateCountdown -=dt;


	if( mGodStateCount > sf::Time::Zero)
	mGodStateCount-=dt;



}





void GameObject::checkStateChange()
{

    if( mGodStateCount <= sf::Time::Zero && mGodStateActive )
    {
        mGodStateActive = false;


    }

    if( mStateCountdown <= sf::Time::Zero && mSuperStateActive)
    {
        mSuperStateActive = false;

    }



//    No active state
    if(!mGodStateActive && !mSuperStateActive)
    {


        if(isPlayer())
        {
            mCurrentState = State::NormalPac;

            return;
        }

    }
//  Both States Active 😵️
    else if(mGodStateActive && mSuperStateActive)
    {
        if(isPlayer())
        {
            mCurrentState = State::SuperNormalPac;
        }
        else
        {

            mCurrentState = State::SuperNormalEnemy;

        }

    }


}


void GameObject::setColor(sf::Color color)
{

    mSprite.setColor(color);

}


void GameObject::setSize(float x, float y)
{
    mSprite.setScale(x,y);


}


void GameObject::setState(unsigned int state)
{
    auto temp_state = static_cast<State>(state);

    switch(temp_state)
    {
        case State::SuperPac :
        mStateCountdown = sf::seconds(7.f);
        mCurrentState = State::SuperPac;
        mSuperStateActive = true;
        break;

        case State::GodPac :
        mGodStateCount = sf::seconds(4.f);
        mCurrentState = State::GodPac;
        mGodStateActive = true;
        break;


        case State::ScaredGhost :
        mCurrentState = State::ScaredGhost;
        break;

        case State::SquishedGhost :
        mCurrentState = State::SquishedGhost;
        break;

        case State::NormalGhost:
        mCurrentState = State::NormalGhost;
        break;

        default:
        break;

    }

}



sf::Vector2f GameObject::getPreviousPosition() const
{

    return mPreviousPosition;
}


unsigned int GameObject::currentState()
{
    return mCurrentState;

}



unsigned int GameObject::getCategory() const
{

	return mCurrentState;
}

sf::FloatRect GameObject::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool GameObject::isMarkedForRemoval() const
{
	return mIsMarkedForRemoval;
}

bool GameObject::isPlayer() const
{
	return mType == Pacman;
}

float GameObject::getMaxSpeed() const
{


	return Table[mType].speed;
}

void GameObject::hasCollided(bool collided)
{

    mCollided = collided;

}



void GameObject::updateMovementPattern(sf::Time dt)
{

	if(mCollided)
    {


         std::vector<sf::Vector2f> directions = { sf::Vector2f(-10,0),
	                                              sf::Vector2f(10,0) ,
	                                              sf::Vector2f(0,10),
	                                              sf::Vector2f(0,-10)
	                                            };


        auto direction = directions[randomInt(directions.size() , 0)];
        auto vx        = getMaxSpeed() * direction.x*dt.asSeconds() ;
        auto vy        = getMaxSpeed() * direction.y*dt.asSeconds() ;


        setVelocity(vx, vy);
        hasCollided(false);

    }



}
