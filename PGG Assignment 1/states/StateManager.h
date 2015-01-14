#include "State.h"
#include <vector>
#include <SDL.h>

#pragma once

class StateManager
{
public:
	StateManager(int windowWidth, int windowHeight);
	~StateManager();

	void addState(State* state);
	void changeState(State* state);
	void popLastState();

	//Pass through function that call the states internal functions
	bool eventHandler();
	void update(float dt);
	void render();

	//Think these are fine to have public since they are const
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;

private:

	void clearStates();
	std::vector<State*> states;

};