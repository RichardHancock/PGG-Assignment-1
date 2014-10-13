// This is the main SDL include file
#include <SDL.h>
// iostream is so we can output error messages to console
#include <iostream>
#include "Texture.h"
#include "Entity.h"
#include "Bullet.h"
#include <vector>

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return -1;
	}

	// Now we have got SDL initialised, we are ready to create a window!
	// These are some variables to help show you what the parameters are for this function
	// You can experiment with the numbers to see what they do
	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 640;
	int winHeight = 480;
	SDL_Window *window = SDL_CreateWindow("My Window!!!",  // The first parameter is the window title
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	// The SDL_Renderer is a structure that handles rendering
	// It will store all of SDL's internal rendering related settings
	// When we create it we tell it which SDL_Window we want it to render to
	// That renderer can only be used for this window
	// (yes, we can have multiple windows - feel free to have a play sometime)
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	Texture* t_player = new Texture("debugSprite.bmp",renderer);
	Entity* player = new Entity(t_player, Vec2(75, 380));
	if (!player)
	{
		//Make better (i.e not external)
		std::cout << "Class wasn't constucted: player" << std::endl;
		SDL_Delay(10000);
		SDL_Quit();
		return -1;
	}
	Texture* bulletSprite = new Texture("bullet.bmp", renderer);
	Texture* background = new Texture("background.bmp", renderer);
	//LAZY Non encapsulated FOR SANITY REMOVE LATER (Merge into entity)
	int speed = 5;

	std::vector<Bullet*> bullets;

	// We are now preparing for our main loop (also known as the 'game loop')
	// This loop will keep going round until we exit from our program by changing the bool 'go' to the value false
	// This loop is an important concept and forms the basis of most games you'll be writing
	// Within this loop we generally do the following things:
	//   * Check for input from the user (and do something about it!)
	//   * Update our world
	//   * Draw our world
	// We will come back to this in later lectures

	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
				case SDLK_a:
					player->move(Vec2(-speed, 0));
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					player->move(Vec2(speed, 0));
					break;
				case SDLK_SPACE:
					Vec2 bulletLineup = player->getPos();

					std::cout << player->getDimensions().x << std::endl;

					bulletLineup.x += (player->getDimensions().x / 2);
					//CONTINUE HERE
					bullets.push_back(new Bullet(bulletSprite,bulletLineup));
					break;
				}


				break;
				// If you want to learn more about event handling and different SDL event types, see:
				// https://wiki.libsdl.org/SDL_Event
				// and also: https://wiki.libsdl.org/SDL_EventType
				// but don't worry, we'll be looking at handling user keyboard and mouse input soon
			}
		}


		// Update our world
		// (nothing to update for now)
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->update();
		}

		// Draw our world

		// Start by clearing what was drawn before
		// Set the colour for drawing, set to red here
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		// Clear the entire screen to our selected colour
		SDL_RenderClear(renderer);

		// To be honest because we're not actually changing anything each time we draw our texture, the whole game loop is a bit of an overkill
		// The point is though, I wanted to show you this way of doing things so that when we *do* change stuff each frame
		// we don't need to think about a whole new program structure!
		// Also, feel free to start playing and see if you can get the texture to move about ;)
		// Or just wait for next week :)
		//background->draw(Vec2(0, 0));
		player->render();
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->render();
		}
		

		// This tells the renderer to actually show its contents to the screen
		// We'll get into this sort of thing at a later date - or just look up 'double buffering' if you're impatient :P
		SDL_RenderPresent(renderer);
	}

	// If we get outside the main game loop, it means our user has requested we exit


	// Our cleanup phase, hopefully fairly self-explanatory ;)
	delete player;
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}