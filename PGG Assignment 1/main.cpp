#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>

#include "Texture.h"
#include "Entity.h"
#include "Bullet.h"
#include "PlayerShip.h"
#include "Background.h"
#include "Utility.h"
#include "ParticleSystem.h"


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

	// Resource Loading (Encapsulate later)
	Texture* bulletSprite = new Texture("laserRed01.png", renderer);

	Texture* t_player = new Texture("ship.png", renderer);
	PlayerShip* player = new PlayerShip(t_player, Vec2(75, 330), bulletSprite);
	
		//Particles
	Texture* particle = new Texture("emitterTest.png", renderer);
	std::vector<Texture*> particleTextures;
	particleTextures.push_back(particle);
	ParticleSystem particleManager(Vec2(240,240), particleTextures, 1);

	particleManager.generateNewParticles();

	Texture* t_background = new Texture("download.bmp", renderer);
	Background* background = new Background(t_background, Vec2(0,0), WIN_HEIGHT, WIN_WIDTH);
	Background* background2 = new Background(t_background, Vec2(0, -480), WIN_HEIGHT, WIN_WIDTH);
	
	TTF_Font *font = TTF_OpenFont("OpenSans-Regular.ttf", 16);
	if (!font) 
	{
		Utility::log(Utility::E,"TTF_OpenFont: " + std::string(TTF_GetError()));
	}

	Vec2 mouse(0, 0);

	unsigned int lastTime = SDL_GetTicks();

	bool quit = false;
	SDL_Event e;

	for (int i = 0; i < 100; i++){
		std::cout << std::setprecision(5) << "1 - 10: " << Utility::randomFloat(1.0, 10.0) << std::endl;
	}
	

	//Main Loop
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{	
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_MOUSEMOTION:
				mouse.x = (float)e.motion.x;
				mouse.y = (float)e.motion.y;
				player->updateMouse(mouse);
			
			default:
				player->eventHandler(e);
				break;
			}

			//Escape Key
			if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}


		// Update
		unsigned int current = SDL_GetTicks();
		float dt = (float)(current - lastTime) / 1000.0f;
		lastTime = current;
		
		player->update(dt);
		background->update(dt);
		background2->update(dt);
		particleManager.update(dt);

		//Render
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		
		background->render();             
		background2->render();

		player->render();
		particleManager.render();

		//Text Test
		SDL_Colour testColour;
		testColour.r = 255;
		testColour.g = 0;
		testColour.b = 0;
		std::string textString = player->isMouseEnabled() ? "Mouse Enabled" : "Mouse Disabled";

		Texture* textTest = new Texture(TTF_RenderUTF8_Solid(font, textString.c_str(), testColour),renderer);
		textTest->draw(Vec2(0, 0));
		delete textTest;

		SDL_RenderPresent(renderer);

		if (dt < (1.0f / 50.0f))	// not sure how accurate the SDL_Delay function is..
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - dt)*1000.0f));
		}
	}

	
	// Delete all classes
	delete player;
	delete background;
	delete background2;

	delete t_background;
	delete t_player;
	delete bulletSprite;
	TTF_CloseFont(font);

	cleanup();

	return 0;
}

void cleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}