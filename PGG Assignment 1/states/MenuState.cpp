#include "MenuState.h"
#include "PlayState.h"

MenuState::MenuState(StateManager* manager, SDL_Renderer* renderer)
	: State(manager, renderer)
{
	stateName = "Menu State";
	mouse = { 0, 0 };
	
	TTF_Font* font = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 32);
	buttonTexture = new Texture("res/images/button.png", renderer);
	SDL_Colour colour = { 255, 255, 255 };
	//Button* play = new Button(Vec2(0, 20), buttonTexture, "Play", font, colour, renderer);

	buttons[Play] = new Button(Vec2(0, 20), buttonTexture, "Play", font, colour, renderer);
	buttons[Options] = new Button(Vec2(0, 170), buttonTexture, "Options", font, colour, renderer);
	buttons[Help] = new Button(Vec2(0, 320), buttonTexture, "Help", font, colour, renderer);
	buttons[Credits] = new Button(Vec2(640 - buttonTexture->getDimensions().x, 460 - buttonTexture->getDimensions().y), 
		buttonTexture, "Credits", font, colour, renderer);
	buttons[Quit] = new Button(Vec2(640 - buttonTexture->getDimensions().x, 310 - buttonTexture->getDimensions().y),
		buttonTexture, "Quit", font, colour, renderer);
	
	TTF_CloseFont(font);
	delete font;
}

MenuState::~MenuState()
{
	delete buttonTexture;
	
	for (auto b : buttons)
	{
		delete b.second;
	}

	buttons.clear();
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