#include "PlayState.h"

PlayState::PlayState(StateManager* manager, SDL_Renderer* renderer)
	: State(manager, renderer)
{
	stateName = "Play State";
}

PlayState::~PlayState()
{

}

bool PlayState::eventHandler()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		
	}

	return true;
}

void PlayState::update(float dt)
{

}

void PlayState::render()
{
	
}
