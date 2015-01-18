#pragma once

#include "Enemy.h"
#include "../particles/ParticleSystem.h"
/**
@class Asteroid
@brief An Asteroid that is thrown at a random velocity towards the ground. Will kill the player.
*/
class Asteroid : public Enemy
{
public:
	/**
	@brief Creates a asteroid
	@param Texture* - Sprite
	@param Vec2 - Starting Position
	@param int - Asteroid Health
	@param int - Damage Capability
	@param Vec2 - Asteroids constant velocity
	@param Texture* - Sprite for particles
	*/
	Asteroid(Texture* sprite, Vec2 pos, int health, int damage, Vec2 velocity, Texture* pTexture);
	
	~Asteroid();

	/**
	@brief Update the internal values
	@param float - delta time
	*/
	void update(float dt);

	/**
	@brief Render the asteroid and its particles
	@param SDL_Rect* - Global camera position to render relative to
	*/
	void render(SDL_Rect* camera);


private:
	ParticleSystem* particles;

	float lifespan;
};