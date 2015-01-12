#include "State.h"
#include "StateManager.h"

#pragma once

class PlayState :public State
{
public:
	PlayState(StateManager* manager, SDL_Renderer* renderer);
	~PlayState();

	bool eventHandler();
	void update(float dt);
	void render();

private:

};