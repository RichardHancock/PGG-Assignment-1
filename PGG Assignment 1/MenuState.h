#include "State.h"
#include "StateManager.h"

#pragma once

class MenuState : public State
{
public:
	MenuState(StateManager* manager, SDL_Renderer* renderer);
	~MenuState();
	bool eventHandler();

	void update(float dt);

	void render();

private:

};