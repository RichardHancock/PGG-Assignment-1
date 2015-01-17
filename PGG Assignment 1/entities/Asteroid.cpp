#include "Asteroid.h"

Asteroid::Asteroid(Texture* sprite, Vec2 pos, int damage, Vec2 velocity)
	: Enemy(sprite, pos, damage)
{
	setVelocity(velocity);
}

void Asteroid::update(float dt)
{
	pos += (velocity * dt);
}