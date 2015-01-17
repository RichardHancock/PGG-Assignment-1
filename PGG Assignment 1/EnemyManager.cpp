#include "EnemyManager.h"
#include "entities/Asteroid.h"

EnemyManager::EnemyManager(float spawnDelay)
	:spawnDelay(spawnDelay), spawning(false)
{

}

EnemyManager::~EnemyManager()
{
	for (auto e : enemies)
	{
		delete e;
	}
	enemies.clear();

	for (auto eSprite : enemySprites)
	{
		delete eSprite.second;
	}
	enemySprites.clear();

	Utility::Timer::stopTimer("SpawnDelay");
}

void EnemyManager::update(float dt)
{
	if (Utility::Timer::hasTimerFinished("SpawnDelay"))
	{
		spawnEnemy();
		Utility::Timer::createTimer("SpawnDelay", spawnDelay);
	}

	for(auto e : enemies)
	{
		e->update(dt);
	}
}

void EnemyManager::render()
{
	for (auto e : enemies)
	{
		e->render();
	}
}

bool EnemyManager::isSpawning()
{
	return spawning;
}

void EnemyManager::toggleSpawning()
{
	spawning = !spawning;
	spawning ? Utility::Timer::createTimer("SpawnDelay",spawnDelay) 
		: Utility::Timer::stopTimer("SpawnDelay");
}

void EnemyManager::spawnEnemy()
{
	//This could be easily exanded for different types of enemies.
	int random = Utility::randomInt(1, 4);

	//Generate a random velocity backwards at a 0-54 degree angle.
	Vec2 randomVelocity;
	randomVelocity.x = -(Utility::randomFloat(0.0f, 1.0f));
	randomVelocity.y = Utility::randomFloat(0.0f, 0.6f);
	// possible multiply here if this is too slow
	
	Vec2 startPos = { 640, 0 };
	Texture* sprite = (random == 4 ? enemySprites["LargeAsteroid"] : enemySprites["SmallAsteroid"]);
	Asteroid* temp = new Asteroid(sprite, startPos, randomVelocity);
	temp->setReducedAABB(85);
	enemies.push_back(temp);



}