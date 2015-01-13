#include "MenuState.h"
#include "PlayState.h"

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
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT) { 
				return click();
			}
		}
	}

	return true;
}

void MenuState::update(float dt)
{

}

void MenuState::render()
{
	/* ugh
	for (std::unordered_map<std::string, Button*>::iterator it = buttons.begin();
		it != buttons.end(); ++it)
	{
		it->second->render();
	}
	*/

	// C++11 makes this awesome
	for(auto b : buttons)
	{
		b.second->render();
	}
}

bool MenuState::click()
{
	for (auto b : buttons)
	{
		if (b.second->isClicked(mouse))
		{
			switch (b.first)
			{
			case Play:
				stateManager->changeState(new PlayState(stateManager, renderer));
				break;
			case Quit:
				return false;
				break;
			default:
				Utility::log(Utility::W, "Unhandled menu button pressed");
				break;
			}
		}
	}

	return true;
}