#include "EntityWithMotion.h"

EntityWithMotion::EntityWithMotion(Texture* texture, Vec2 pos, float maxVelocity, float maxRotationSpeed)
	: Entity(texture, pos), maxVelocity(maxVelocity), maxRotationSpeed(maxRotationSpeed)
{
	rotationSpeed = 0;
	velocity = { 0, 0 };
}

Vec2 EntityWithMotion::getVelocity() { return velocity; }

void EntityWithMotion::setVelocity(Vec2 velocity)
{
	velocity = velocity;
}

float EntityWithMotion::getRotationSpeed() { return rotationSpeed; }

void EntityWithMotion::setRotationSpeed(float rotationSpeed)
{
	rotationSpeed = rotationSpeed;
}