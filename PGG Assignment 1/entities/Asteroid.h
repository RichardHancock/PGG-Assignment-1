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
	@param int - Damage Capability
	@param Vec2 - Asteroids constant velocity
	*/
	Asteroid(Texture* sprite, Vec2 pos, int damage, Vec2 velocity);
	
	/**
	@brief Update the internal values
	@param float - delta time
	*/
	void update(float dt);

private:
	ParticleSystem* particles;
};