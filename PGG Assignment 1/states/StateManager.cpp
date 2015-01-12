#include "StateManager.h"
#include "State.h"
#include "../Utility.h"

StateManager::~StateManager()
{
	clearStates();
}

void StateManager::clearStates()
{
	for (int i = 0; i < (int)states.size(); i++)
	{
		delete states[i];
	}
	states.clear();
}

void StateManager::addState(State* state)
{
	states.push_back(state);
	Utility::log(Utility::I, "StateManager: Switched to the " + state->getStateName());
}

void StateManager::changeState(State* state)
{
	clearStates();
	addState(state);
}

void StateManager::popLastState()
{
	delete states.back();
	states.pop_back();
}

bool StateManager::eventHandler()
{
	return states.back()->eventHandler();
}

void StateManager::update(float dt)
{
	states.back()->update(dt);
}

void StateManager::render()
{
	for (int i = 0; i < (int)states.size(); i++)
	{
		states[i]->render();
	}
}