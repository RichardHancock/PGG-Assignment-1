#include "MenuState.h"

MenuState::MenuState(StateManager* manager, SDL_Renderer* renderer)
	: State(manager, renderer)
{
	stateName = "Menu State";
}

MenuState::~MenuState()
{

}

bool MenuState::eventHandler()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{

	}

	return true;
}

void MenuState::update(float dt)
{

}

void MenuState::render()
{

}
