#include "State.h"
#include "StateManager.h"

#include "../Utility.h"
#include "../Texture.h"
#include "../entities/Player.h"
#include "../particles/ParticleSystem.h"
#include "../levelManagement/LevelManager.h"
#include "../Music.h"
#include "../SFX.h"
#include "../EnemyManager.h"

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
	/**
	@brief Check for collisions between the player and the world
	@param float - delta time
	@param LevelManager - Level manager containing the level data
	@param Player - The player object
	*/
	void worldCollisions(float dt, LevelManager &levels, Player &player);

	/**
	@brief Check for collisions between the player and the enemies
	@param EnemyManager - Enemy manager containing the enemies
	@param Player - The player object
	*/
	void enemyCollisions(EnemyManager &enemies, Player &player);

	/**
	@brief Checks if a game over has occurred (Reach end of level
	@todo Add a game over screen, currently only prints to console.
	*/
	void checkGameOver();

	void loadResources();

	Texture* bulletSprite;
	Texture* playerSprite;

	SDL_Rect camera;

	//Temp until level switching added
	std::string currentLevel = "Level 1";

	LevelManager* levels;
	Player* player;

	EnemyManager* enemyManager;

	Music* music;
};