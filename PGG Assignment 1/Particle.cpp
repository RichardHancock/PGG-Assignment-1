#include "Particle.h"

Particle::Particle(Texture* texture, Vec2 pos, float maxVelocity, float maxRotationSpeed, Colour colour, float lifespan)
	: EntityWithMotion(texture, pos, maxVelocity, maxRotationSpeed), colour(colour), lifespan(lifespan)
{

}

void Particle::update(float dt)
{
	pos += velocity * dt;
}

