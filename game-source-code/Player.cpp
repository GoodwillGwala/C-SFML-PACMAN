#include "Player.h"
#include "CommandQueue.h"
#include "GameObject.h"
#include "Foreach.h"

#include <map>
#include <string>
#include <algorithm>

using namespace std::placeholders;


struct GameObjectMover //should make available for all GameObjects
{
	GameObjectMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (GameObject& GameObject, sf::Time) const
	{
		GameObject.setVelocity(velocity * GameObject.getMaxSpeed());

	}

	sf::Vector2f velocity;
};

Player::Player()
: mCurrentMissionStatus(MissionRunning)
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;


	// Set initial action bindings
	initializeActions();

	// Assign all categories to player's GameObject
	FOREACH(auto& pair, mActionBinding)
		pair.second.category = Category::PlayerGameObject;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{


	FOREACH(auto pair, mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first))
			commands.push(mActionBinding[pair.second]);
	}

}


void Player::setMissionStatus(MissionStatus status)
{
	mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
	return mCurrentMissionStatus;
}

void Player::initializeActions()
{
	mActionBinding[MoveLeft].action      = derivedAction<GameObject>(GameObjectMover(-1,  0));
	mActionBinding[MoveRight].action     = derivedAction<GameObject>(GameObjectMover(+1,  0));
	mActionBinding[MoveUp].action        = derivedAction<GameObject>(GameObjectMover( 0, -1));
	mActionBinding[MoveDown].action      = derivedAction<GameObject>(GameObjectMover( 0, +1));

}
