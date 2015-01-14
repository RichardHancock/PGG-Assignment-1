#include "State.h"
#include "StateManager.h"

#include "../Utility.h"
#include "../Texture.h"
#include "../entities/Player.h"
#include "../particles/ParticleSystem.h"
#include "../levelManagement/LevelManager.h"

#pragma once

class PlayState :public State
{
public:
	PlayState(StateManager* manager, SDL_Renderer* renderer, 
		unsigned int level);
	~PlayState();

	bool eventHandler();
	void update(float dt);
	void render();

private:
	void collisions(float dt, LevelManager &levels, Player &player);

	void loadResources();

	Texture* bulletSprite;
	Texture* playerSprite;
	std::vector<Texture*> particleSprites;

	SDL_Rect camera;

	LevelManager* levels;
	Player* player;
	ParticleSystem* particleTest;
};