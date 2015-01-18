#pragma once

#include <vector>
#include <unordered_map>

#include "entities/Enemy.h"

class EnemyManager
{
public:
	EnemyManager(std::unordered_map<std::string, Texture*> enemySprites,float spawnDelay);
	~EnemyManager();

	/**
	@brief Update all the enemies
	@param float - deltatime
	@param Vec2 - The top right screen position (Get from camera.x + screen Width, camera.y)
	*/
	void update(float dt, SDL_Rect* camera);

	///Render all the enemies
	void render(SDL_Rect* camera);

	/**
	@brief Is the EnemyManager currently set to spawn enemies
	@return bool - True if spawning, false if not
	*/
	bool isSpawning();

	/**
	@brief Tells the spawner to start/stop spawning
	*/
	void toggleSpawning();

private:
	float spawnDelay;

	bool spawning;

	/**
	@brief Spawns Enemies
	@param Vec2 - The top right screen position (Get from camera.x + screen Width, camera.y)
	*/
	void spawnEnemy(Vec2 topRightScreenPos);

	std::vector<Enemy*> enemies;

	std::unordered_map<std::string, Texture*> enemySprites;
};