// This is the main SDL include file
#include <SDL.h>
#include <SDL_image.h>
// iostream is so we can output error messages to console
#include <iostream>
#include "Texture.h"
#include "Entity.h"
#include "Bullet.h"
#include <vector>


/*

void update(float dt)
{

}

void draw()
{

}
//For The complicated timer
#include <windows.h>
#include <cstdint>
#include <time.h>

float g_startOfFrame, g_endOfFrame, g_rateInv;
int64_t g_startTick;

void initFrameTimer()
{
	
	int64_t rate;
	g_rateInv = 1.0f / (float)CLOCKS_PER_SEC;

	if (!QueryPerformanceCounter((LARGE_INTEGER*)&rate))
	{
		return;
	}
	if (!rate)
	{
		return;
	}
	
	g_rateInv = 1.0f / (float)rate;
	if (!QueryPerformanceCounter((LARGE_INTEGER*)&g_startTick))
	{
		return;
	}
}

float currentTime()
{
	int64_t endTick;
	QueryPerformanceCounter((LARGE_INTEGER*)&endTick);
	return (endTick - g_startTick) * g_rateInv;
}

void onIdle()
{
	do 
	{
		g_endOfFrame = currentTime();
	} 
	while (g_endOfFrame == g_startOfFrame);

	float dt = g_endOfFrame - g_startOfFrame;
	g_startOfFrame = g_endOfFrame;

	update(dt);
	//Define these
	draw();
}

//End of Timer stuff

*/

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return -1;
	}

	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 640;
	int winHeight = 480;
	SDL_Window *window = SDL_CreateWindow("My Window!!!",  // The first parameter is the window title
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	Texture* t_player = new Texture("ship.png", renderer);
	Entity* player = new Entity(t_player, Vec2(75, 330));
	if (!player)
	{
		//Make better (i.e not external)
		std::cout << "Class wasn't constucted: player" << std::endl;
		SDL_Delay(10000);
		SDL_Quit();
		return -1;
	}
	Texture* bulletSprite = new Texture("bullet.bmp", renderer);
	Texture* background = new Texture("download.bmp", renderer);
	Texture* background2 = new Texture("download.bmp", renderer);
	int backgroundY = 0;
	int background2Y = -480;
	
	//LAZY Non encapsulated FOR SANITY REMOVE LATER (Merge into entity)
	int speed = 5;

	std::vector<Bullet*> bullets;

	bool mv_left = false;
	bool mv_right = false;
	bool firing = false;
	int delay = 0;
	// We are now preparing for our main loop (also known as the 'game loop')
	// This loop will keep going round until we exit from our program by changing the bool 'go' to the value false
	// This loop is an important concept and forms the basis of most games you'll be writing
	// Within this loop we generally do the following things:
	//   * Check for input from the user (and do something about it!)
	//   * Update our world
	//   * Draw our world
	// We will come back to this in later lectures

	unsigned int lastTime = SDL_GetTicks();

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
			case SDL_MOUSEMOTION:
				e.motion.x;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
				case SDLK_a:
					mv_left = true;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					mv_right = true;
					break;
				case SDLK_SPACE:
					firing = true;
					
					break;
				}
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
				case SDLK_a:
					mv_left = false;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					mv_right = false;
					break;
				case SDLK_SPACE:
					firing = false;
					break;
				}
				
			}
		}


		// Update our world
		// (nothing to update for now)
		unsigned int current = SDL_GetTicks();
		float deltaTs = (float)(current - lastTime) / 1000.0f;
		lastTime = current;

		float velocityY = 0.0f;
		float velocityX = 0.0f;

		if (mv_left &!mv_right)
		{
			// We are told to move left
			velocityX = -200.0f;
		}
		if (mv_right &!mv_left)
		{
			// We are told to move right
			velocityX = 200.0f;
		}
		if (firing && delay > 10)
		{
			Vec2 bulletLineup = player->getPos();

			std::cout << player->getDimensions().x << std::endl;

			bulletLineup.x += (player->getDimensions().x / 2) - (bulletSprite->getDimensions().x / 2);
			//CONTINUE HERE
			bullets.push_back(new Bullet(bulletSprite, bulletLineup));
			delay = 0;
		}
		delay++;
		player->move(Vec2((unsigned int) (velocityX * deltaTs), 0));

		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->update();
		}
		
		
		backgroundY++;
		background2Y++;
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		background2->draw(Vec2(0, background2Y));
		background->draw(Vec2(0, backgroundY));             
		if (backgroundY >= 480) {
			backgroundY = -480;
		}
		if (background2Y >= 480) {
			background2Y = -480;
		}
		player->render();
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->render();
		}
		
		
		SDL_RenderPresent(renderer);

		if (deltaTs < (1.0f / 50.0f))	// not sure how accurate the SDL_Delay function is..
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
		}
	}

	delete player;
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}