#include "Particle.h"

Particle::Particle(Texture* texture, Vec2 pos, float maxVelocity, float maxRotationSpeed, Colour colour, float lifespan)
	: EntityWithMotion(texture, pos, maxVelocity, maxRotationSpeed), colour(colour), lifespan(lifespan)
{
	sprite->setColourTint(colour);
}

void Particle::update(float dt)
{
	//Apply velocity
	pos += ((velocity * 10) * dt);

	//Lower lifespan
	lifespan -= dt;
}

void Particle::render()
{
	sprite->draw(pos, rotation);
}

bool Particle::hasExpired()
{
	if(lifespan <= 0.00f)
	{
		return true;
	}
	else
	{
		return false;
	}
}