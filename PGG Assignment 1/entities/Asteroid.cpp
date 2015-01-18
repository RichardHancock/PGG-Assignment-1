#include "Asteroid.h"

Asteroid::Asteroid(Texture* sprite, Vec2 pos, int damage, Vec2 velocity)
	: Enemy(sprite, pos, damage)
{
	setVelocity(velocity);

	//Particle colour random range R 200 - 255 G 0 - 80 B 0
}

void Asteroid::update(float dt)
{
	pos += (velocity * dt);
}