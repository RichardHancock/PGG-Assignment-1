#include "State.h"
#include <vector>
#include <SDL.h>

#pragma once

class StateManager
{
public:
	~StateManager();

	void addState(State* state);
	void changeState(State* state);
	void popLastState();

	//Pass through function that call the states internal functions
	bool eventHandler();
	void update(float dt);
	void render();

private:

	void clearStates();
	std::vector<State*> states;

};