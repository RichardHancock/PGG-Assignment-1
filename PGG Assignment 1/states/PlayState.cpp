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
	enemyManager = new EnemyManager(enemiesTextures, 6);
	enemyManager->toggleSpawning();

	music = new Music("res/audio/test.wav");
	music->play(0, 0);
}

PlayState::~PlayState()
{
	// Delete all classes
	delete player;

	// Delete all resources
	delete playerSprite;
	delete bulletSprite;

	for (Texture* p : particleSprites)
	{
		delete p;
	}
	particleSprites.clear();

	delete enemyManager;
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
	particleTest->update(dt);
	levels->getLevel(currentLevel)->update(dt);
	collisions(dt, *levels, *player);
	player->update(dt);
	enemyManager->update(dt);

	checkGameOver();
}

void PlayState::render()
{
	levels->getLevel("Level 1")->render(&camera);
	player->render();
	particleTest->render();
	enemyManager->render();
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

	Texture* particle = new Texture(dir + "emitterTestSmall.png", renderer);
	particleSprites.push_back(particle);
	particleTest = new ParticleSystem(Vec2(240, 350), particleSprites, 3, Vec2(0, -10));
	particleTest->generateNewParticles();
}


void PlayState::collisions(float dt, LevelManager &levels, Player &player)
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
					player.setVelocity(Vec2(0, player.getVelocity().y));
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
