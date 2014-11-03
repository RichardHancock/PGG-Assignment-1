#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Texture.h"
#include "Entity.h"
#include "Bullet.h"
#include <vector>


int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Something went very wrong in initialization, all we can do is exit
		std::cout << "Whoops! Something went very wrong, cannot initialize SDL :(" << std::endl;
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
		std::cout << "Class wasn't constructed: player" << std::endl;
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
	Vec2 mouse(0, 0);
	bool mouseEnabled = false;
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
				mouse.x = e.motion.x;
				mouse.y = e.motion.y;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
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
				case SDLK_q:
					mouseEnabled = !mouseEnabled;
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
		//Mouse
		if (mouseEnabled)
		{
			int mouseOffsetLeft = (player->getPos().x + (player->getDimensions().x / 2)) - 20;
			int mouseOffsetRight = mouseOffsetLeft + 40;

			if (mouse.x < mouseOffsetLeft)
			{
				velocityX = -200.0f;
			}
			if (mouse.x > mouseOffsetRight)
			{
				velocityX = 200.0f;
			}
		}



		if (firing && delay > 10)
		{
			Vec2 bulletLineup = player->getPos();
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
			if (bullets[i]->getPos().y < -30)
			{
				bullets.erase(bullets.begin() + i);
			}
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