#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>

#include "Utility.h"
#include "states/StateManager.h"
#include "states/MenuState.h"

int init();
int main(int, char*[]);
void cleanup();

//Constants
const int WIN_POS_X = 100;
const int WIN_POS_Y = 100;
const int WIN_WIDTH = 640;
const int WIN_HEIGHT = 480;

//globals
SDL_Window *window;
SDL_Renderer *renderer;

int init()
{
	int status = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) { status = -1; }
	if (TTF_Init() < 0) 
	{ 
		status = -1;
		Utility::log(Utility::E,"SDL_ttf init failed: " + std::string(TTF_GetError()));
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		status = -1;
		Utility::log(Utility::E, "SDL_mixer init failed: " + std::string(Mix_GetError()));
	}

	window = SDL_CreateWindow("SDL Practice",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!window || !renderer) { status = -1; }
	
	if (status == -1)
	{
		Utility::log(Utility::E, "Error occurred in init: " + std::string(SDL_GetError()));
	}

	Utility::randomInit();

	return status;
}

int main(int argc, char *argv[])
{
	if (init() == -1) { return -1; }

	StateManager* stateManager = new StateManager(WIN_WIDTH, WIN_HEIGHT);
	stateManager->addState(new MenuState(stateManager, renderer));

	unsigned int lastTime = SDL_GetTicks();

	bool quit = false;
	
	//Main Loop
	while (!quit)
	{
		quit = (stateManager->eventHandler() ? false : true);

		// Update
		//Calculate deltaTime
		unsigned int current = SDL_GetTicks();
		float dt = (float)(current - lastTime) / 1000.0f;
		lastTime = current;
		
		stateManager->update(dt);

		//Render
		SDL_RenderClear(renderer);
		
		stateManager->render();

		SDL_RenderPresent(renderer);

		if (dt < (1.0f / 50.0f))	// not sure how accurate the SDL_Delay function is..
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - dt)*1000.0f));
		}
	}

	delete stateManager;

	cleanup();
	return 0;
}

void cleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}