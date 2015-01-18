#include "PlayState.h"
#include "MenuState.h"

PlayState::PlayState(StateManager* manager, SDL_Renderer* renderer,
	unsigned int level)
	: State(manager, renderer)
{
	stateName = "Play State";
	///@todo Change Level manager to use the uint level parameter
	
	loadResources();

	//camera.x is updated every update loop
	camera.x = 0;
	camera.y = 0;
	camera.h = stateManager->WINDOW_HEIGHT;
	camera.w = stateManager->WINDOW_WIDTH;

	//Load Level
	levels = new LevelManager("res/levels/Level 1.lvl", renderer);
	player->setPos(levels->getLevel(currentLevel)->getStartPos());

	//Enemies
	std::unordered_map<std::string, Texture*> enemiesTextures;
	enemiesTextures["LargeAsteroid"] = new Texture("res/images/largeAsteroid.png", renderer);
	enemiesTextures["SmallAsteroid"] = new Texture("res/images/smallAsteroid.png", renderer);
	enemiesTextures["AsteroidParticle"] = new Texture("res/images/emitterTestSmall.png", renderer);
	enemyManager = new EnemyManager(enemiesTextures, 3);
	enemyManager->toggleSpawning();

	music = new Music("res/audio/Deep Haze.ogg");
	music->play(0, -1);
}

PlayState::~PlayState()
{
	// Delete all classes
	delete player;

	// Delete all resources
	delete playerSprite;
	delete bulletSprite;

	delete enemyManager;
	
	delete music;
}

bool PlayState::eventHandler()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			player->eventKeyboard(e);
			break;
		case SDL_KEYUP:
			player->eventKeyboard(e);

			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				music->stop(100);
				//Add Pause here instead
				stateManager->changeState(new MenuState(stateManager,renderer));
			}
			break;
		case SDL_QUIT:
			return false;
			break;
		}
	}

	return true;
}

void PlayState::update(float dt)
{
	Utility::Timer::update(dt);

	// Work out current screen pos (This is used to only render on screen tiles. Massive performance saver)
	camera.x = (int)player->getPos().x;

	player->updateVelocities(dt);
	levels->getLevel(currentLevel)->update(dt);
	worldCollisions(dt, *levels, *player);
	enemyCollisions(*enemyManager, *player);
	player->update(dt);
	enemyManager->update(dt, &camera);

	checkGameOver();
}

void PlayState::render()
{
	levels->getLevel("Level 1")->render(&camera);
	player->render();
	enemyManager->render(&camera);
}

void PlayState::checkGameOver()
{
	if (SDL_HasIntersection(&player->getAABB(), &levels->getLevel(currentLevel)->getEndBox()))
	{
		//TODO
		Utility::log(Utility::I, "Game Won!");
	}
}

void PlayState::loadResources()
{
	std::string dir = "res/images/";
	bulletSprite = new Texture(dir + "laser.png", renderer);
	playerSprite = new Texture(dir + "player.png", renderer);

	player = new Player(playerSprite, Vec2(360, 200), bulletSprite);
}

//I have no idea how this works anymore, it has quite iritating bugs that I cannot fix without scraping it entirely

void PlayState::worldCollisions(float dt, LevelManager &levels, Player &player)
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

			bool hitLeft = false;
			bool hitRight = false;

			if (movingLeft)
			{
				if (tilesToProcess[i]->getPos().x + tileAABB.w >= playerNewPos.x)
				{
					player.setVelocity(Vec2(0, player.getVelocity().y));
					hitLeft = true;
				}
			}
			else if (movingRight)
			{
				if (tilesToProcess[i]->getPos().x <= playerNewPos.x + playerNew.w)
				{
					hitRight = true;
					player.setVelocity(Vec2(0, player.getVelocity().y));
				}
			}


			//test y
			if (player.getVelocity().y < 0.0f)
			{
				movingUp = true;
			}
			else if (player.getVelocity().y > 0.0f)
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
			if (movingDown && !hitLeft && !hitRight)
			{
				if (tilesToProcess[i]->getPos().y <= playerNewPos.y + playerNew.h )
				{
					stillLanded = true;
					//if (!player.landed)
					//{
						player.setVelocity(Vec2(player.getVelocity().x, 0));
						float newYPos = (tilesToProcess[i]->getPos().y) - player.getDimensions().y;
						player.setPos(Vec2(player.getPos().x, newYPos));
						player.landed = true;
					//}
					
				}
			}
		}
	}

	player.landed = stillLanded;
}

void PlayState::enemyCollisions(EnemyManager &enemies, Player &player)
{
	//Checks for any collisions with enemies and then applies any damage to the player
	player.hit(enemies.playerCollision(&player.getAABB()));
}