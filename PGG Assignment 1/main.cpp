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
#include "Player.h"
#include "Background.h"
#include "Utility.h"
#include "ParticleSystem.h"
#include "LevelManager.h"

int init();
int main(int, char*[]);
void cleanup();
void collisions(float dt, LevelManager &levels, Player &player);

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
	Texture* bulletSprite = new Texture("res/images/laser.png", renderer);

	Texture* t_player = new Texture("res/images/player.png", renderer);
	Player* player = new Player(t_player, Vec2(360, 200), bulletSprite, 10);
	
	//Particles
	Texture* particle = new Texture("res/images/emitterTestSmall.png", renderer);
	std::vector<Texture*> particleTextures;
	particleTextures.push_back(particle);
	ParticleSystem particleManager(Vec2(240, 350), particleTextures, 3, Vec2(0, -10));

	particleManager.generateNewParticles();	

	LevelManager levels("res/levels/Level 1.lvl", renderer);

	TTF_Font *font = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 16);
	if (!font) 
	{
		Utility::log(Utility::E,"TTF_OpenFont: " + std::string(TTF_GetError()));
	}

	Vec2 mouse(0, 0);

	unsigned int lastTime = SDL_GetTicks();

	bool quit = false;
	SDL_Event e;
	
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
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				player->eventKeyboard(e);
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
		
		SDL_Rect camera;
		camera.x = (int)player->getPos().x;
		camera.y = 0;
		camera.h = WIN_HEIGHT;
		camera.w = WIN_WIDTH;

		player->updateVelocities(dt);
		particleManager.update(dt);
		levels.getLevel("Level 1")->update(dt);
		collisions(dt, levels, *player);
		player->update(dt);
		//Render
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		
		levels.getLevel("Level 1")->render(&camera);
		player->render();
		particleManager.render();

		//Text Test
		SDL_Colour testColour = {255, 0, 0};
		std::string textString = "Level 1";

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

	// Delete all resources
	delete t_player;
	delete bulletSprite;
	TTF_CloseFont(font);

	cleanup();
	return 0;
}

void collisions(float dt, LevelManager &levels, Player &player)
{
	//Calculate the area that collisions will need to be calculated in.
	Vec2 playerNewPos = player.getPos() + (player.getVelocity() * dt);
	SDL_Rect playerOld = player.getAABB();
	SDL_Rect playerNew = playerOld;
	playerNew.x = (int)playerNewPos.x;
	playerNew.y = (int)playerNewPos.y;
	Vec2 playerNewCenter = Utility::getRectCenter(playerNew);
	SDL_Rect result;
	SDL_UnionRect(&playerOld, &playerNew, &result);

	std::vector<Tile*> tilesToProcess = levels.getLevel("Level 1")->checkTiles(result);
	
	bool stillLanded = false;

	for (int i = 0; i < (int)tilesToProcess.size(); i++)
	{
		SDL_Rect tileAABB = tilesToProcess[i]->getAABB();
		if (SDL_HasIntersection(&tileAABB, &playerNew))
		{
			Vec2 leftSide = playerNewPos;
			leftSide.y += playerNew.h / 2;
			Vec2 rightSide = leftSide;
			rightSide.x += playerNew.w;
			Vec2 topSide = playerNewPos;
			topSide.x += playerNew.w / 2;
			Vec2 bottomSide = topSide;
			bottomSide.y += playerNew.h;
				
			//test x
			bool movingLeft = false;
			bool movingRight = false;
			bool movingUp = false;
			bool movingDown = false;

			if (player.getVelocity().x < 0.0f)
			{
				movingLeft = true;
				//player.setVelocity(Vec2(0, player.getVelocity().y));
			}
			else if (player.getVelocity().x > 0.0f)
			{
				movingRight = true;
			}

			if (movingLeft)
			{
				if (tilesToProcess[i]->getPos().x + tileAABB.w >= playerNewPos.x)
				{
					player.setVelocity(Vec2(0,player.getVelocity().y));
				}
			}
			else if (movingRight)
			{
				if (tilesToProcess[i]->getPos().x <= playerNewPos.x + playerNew.w)
				{
					player.setVelocity(Vec2(0, player.getVelocity().y));
				}
			}


			//test y
			if (player.getVelocity().y < -0.01f)
			{
				movingUp = true;
			}
			else if (player.getVelocity().y > 0.01f)
			{
				movingDown = true;
			}


			if (movingUp)
			{
				if (tilesToProcess[i]->getPos().y + tileAABB.h >= playerNewPos.y)
				{
					player.setVelocity(Vec2(player.getVelocity().x, 0));
				}
			}
			else if (movingDown)
			{
				if (tilesToProcess[i]->getPos().y <= playerNewPos.y + playerNew.h)
				{
					stillLanded = true;
					if (!player.landed)
					{
						player.setVelocity(Vec2(player.getVelocity().x, 0));
						player.move(Vec2(0, -2));
						player.landed = true;
					}
				}
			}
		}
	}

	player.landed = stillLanded;
}

void cleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}