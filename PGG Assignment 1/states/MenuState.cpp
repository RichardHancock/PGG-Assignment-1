#include "MenuState.h"
#include "PlayState.h"

MenuState::MenuState(StateManager* manager, SDL_Renderer* renderer)
	: State(manager, renderer)
{
	stateName = "Menu State";
	mouse = { 0, 0 };
	
	TTF_Font* font = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 32);
	if (!font)
	{
		Utility::log(Utility::E, "TTF_OpenFont in MenuState: " + std::string(TTF_GetError()));
	}
	//Create all the buttons
	buttonTexture = new Texture("res/images/button.png", renderer);
	SDL_Colour colour = { 255, 255, 255 };
	buttons[Play] = new Button(Vec2(0, 20), buttonTexture, "Play", font, colour, renderer);
	buttons[Quit] = new Button(Vec2(640 - buttonTexture->getDimensions().x, 460 - buttonTexture->getDimensions().y),
		buttonTexture, "Quit", font, colour, renderer);
	
	TTF_CloseFont(font);
	font = nullptr;

	logo = new Texture("res/images/logo.png", renderer);
	background = new Texture("res/images/Space3.png", renderer);

	music = new Music("res/audio/Take a Chance.ogg");
	music->play(100, -1);
}

MenuState::~MenuState()
{
	delete buttonTexture;
	
	for (auto b : buttons)
	{
		delete b.second;
	}

	buttons.clear();

	delete background;
	delete logo;
	delete music;

}

bool MenuState::eventHandler()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_MOUSEMOTION:
			mouse.x = (float)e.motion.x;
			mouse.y = (float)e.motion.y;
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT) { 
				return click();
			}
			break;

		case SDL_KEYUP:
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				return false;
			}
			break;
		case SDL_QUIT:
			return false;
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
	/* ugh
	for (std::unordered_map<std::string, Button*>::iterator it = buttons.begin();
		it != buttons.end(); ++it)
	{
		it->second->render();
	}
	*/

	background->draw(Vec2(0, 0));
	logo->draw(Vec2(50, 300));

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
				//This has to be here otherwise it stops the new music
				music->stop(100);
				stateManager->prepareToChangeState();
				stateManager->changeState(new PlayState(stateManager, renderer, 1));
				
				break;
			case Quit:
				return false;
				break;
			default:
				Utility::log(Utility::W, "Unhandled menu button pressed");
				break;
			}

			//A button has been pressed, its pointless and dangerous to continue looping.
			break;
		}
	}

	return true;
}