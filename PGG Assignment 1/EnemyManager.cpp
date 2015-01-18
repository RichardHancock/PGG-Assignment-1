#include "EnemyManager.h"
#include "entities/Asteroid.h"

EnemyManager::EnemyManager(std::unordered_map<std::string, Texture*> enemySprites, float spawnDelay)
	:spawnDelay(spawnDelay), spawning(false), enemySprites(enemySprites)
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

void EnemyManager::update(float dt, SDL_Rect* camera)
{ 
	if (Utility::Timer::hasTimerFinished("SpawnDelay"))
	{
		Vec2 topRightScreenPos;
		topRightScreenPos.x = (float)(camera->x + camera->w);
		topRightScreenPos.y = (float)camera->y;
		spawnEnemy(topRightScreenPos);
		Utility::Timer::createTimer("SpawnDelay", spawnDelay);
	}

	for(auto e : enemies)
	{
		e->update(dt);
	}
}

void EnemyManager::render(SDL_Rect* camera)
{
	for (auto e : enemies)
	{
		e->render(camera);
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

void EnemyManager::spawnEnemy(Vec2 topRightScreenPos)
{
	//This could be easily expanded for different types of enemies.
	int random = Utility::randomInt(1, 4);

	//Generate a random velocity backwards at a 0-54 degree angle.
	Vec2 randomVelocity;
	//randomVelocity.x = -(Utility::randomFloat(0.0f, 1.0f));
	randomVelocity.x = -1.0f;
	randomVelocity.y = Utility::randomFloat(0.0f, 0.6f);
	
	///@todo *= operator overload hasn't been implemented 
	randomVelocity = randomVelocity * 100;
	
	Vec2 startPos = topRightScreenPos;
	Texture* sprite = (random == 4 ? enemySprites["LargeAsteroid"] : enemySprites["SmallAsteroid"]);
	Asteroid* temp = new Asteroid(sprite, startPos, 1, randomVelocity, enemySprites["AsteroidParticle"]);
	temp->setReducedAABB(85);
	enemies.push_back(temp);



}