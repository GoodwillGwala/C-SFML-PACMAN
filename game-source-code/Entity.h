/**
*@class <Entity>
*@brief This class provides the definition of an Entity node and it's characteristics.
*this class inherits from Component.
*It characterises an entities movement, livelyhood, rewards and existence.
*
*/
#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"


class Entity : public Component
{
	public:
        /**
        *@brief Constructor.
        *@param health of entity.
        *This implies that game objects have different health statuses.
        */

		explicit                        Entity(int Health);


		/**
        *@brief function to set entity velocity.
        *@param velocity vector.
        */
		void                            setVelocity(sf::Vector2f velocity);
		void                            setVelocity(float vx, float vy);

        /**
        *@brief function to give information about entities current velocity.
        *@return velocity vector
        */
		sf::Vector2f                    getVelocity() const;
        /**
        *@brief function to give information about entities rewards.
        *@return score
        */
		int	                            getScore() const;
		/**
        *@brief function to reward entity.
        *@param points
        */
		void                            reward(int points);
		/**
        *@brief function to damage entity.
        *This function reduces the entities health.
        */
		void                            damage();
		/**
        *@brief function provides information about entity health status.
        *@return health status
        */
		int                             getHealth();
		/**
        *@brief function to destroy entity.
        *This disregards current entity health
        */
		void                            destroy();
		/**
        *@brief function provides information about entity existence.
        *@return flag whether it is alive or not.
        */
		virtual bool                    isDestroyed() const;
        /**
        *@brief function provides information about the amount of pickups collected.
        *@return integer count of pickups collected
        */
		int                             pickupcount();


	protected:

		virtual void                    updateCurrent(sf::Time dt, CommandQueue& commands);


	private:
		sf::Vector2f                    mVelocity;

		int                             mPoints;
		int                             mHealth;
		int                             mPickups;
};

#endif
