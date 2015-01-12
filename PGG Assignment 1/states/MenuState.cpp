#include "MenuState.h"

MenuState::MenuState(StateManager* manager, SDL_Renderer* renderer)
	: State(manager, renderer)
{
	stateName = "Menu State";
	mouse = { 0, 0 };
}

MenuState::~MenuState()
{

}

bool MenuState::eventHandler()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
			break;

		case SDL_MOUSEMOTION:
			mouse.x = (float)e.motion.x;
			mouse.y = (float)e.motion.y;
			break;
		}
	}

	return true;
}

void MenuState::update(float dt)
{

}

void MenuState::render()
{

}
