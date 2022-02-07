#include "GameStateMachine.h"
#include "Foreach.h"

#include <cassert>


GameStateMachine::GameStateMachine(State::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{
}

void GameStateMachine::update(sf::Time dt)
{

	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void GameStateMachine::draw()
{

	FOREACH(State::Ptr& state, mStack)
		state->draw();
}

void GameStateMachine::handleEvent(const sf::Event& event)
{

	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			break;
	}

	applyPendingChanges();
}

void GameStateMachine::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

void GameStateMachine::popState()
{
	mPendingList.push_back(PendingChange(Pop));
}

void GameStateMachine::clearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

bool GameStateMachine::isEmpty() const
{
	return mStack.empty();
}

State::Ptr GameStateMachine::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void GameStateMachine::applyPendingChanges()
{
	FOREACH(PendingChange change, mPendingList)
	{
		switch (change.action)
		{
			case Push:
				mStack.push_back(createState(change.stateID));
				break;

			case Pop:
				mStack.pop_back();
				break;

			case Clear:
				mStack.clear();
				break;
		}
	}

	mPendingList.clear();
}

GameStateMachine::PendingChange::PendingChange(Action action, States::ID stateID)
: action(action)
, stateID(stateID)
{
}
