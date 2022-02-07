#include "State.h"
#include "GameStateMachine.h"



State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player)
:textures(&textures)
,fonts(&fonts)
,window(&window)
,player(&player)
{}

State::State(GameStateMachine& machine, Context context)
:m_machine(&machine)
,mContext(context)
{}

void State::requestStackPush(States::ID stateID)
{
	m_machine->pushState(stateID);
}

void State::requestStackPop()
{
	m_machine->popState();
}

void State::requestStateClear()
{
	m_machine->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}

State::~State()
{
}
