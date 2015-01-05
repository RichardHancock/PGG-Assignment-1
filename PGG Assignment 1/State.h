#include <SDL.h>
#include <string>

#pragma once
class StateManager;

//Reference: Pete Allen's Game State Example

class State
{
public:
	State(StateManager* manager, SDL_Renderer* renderer);
	virtual ~State() {}

	virtual bool eventHandler() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;

	std::string getStateName() { return stateName; }
protected:
	StateManager* stateManager;
	SDL_Renderer* renderer;
	std::string stateName;
};