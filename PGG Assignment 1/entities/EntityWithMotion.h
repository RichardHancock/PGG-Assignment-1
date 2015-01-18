#include "Entity.h"

#pragma once

class EntityWithMotion : public Entity
{
public:
	EntityWithMotion(Texture*, Vec2);
	EntityWithMotion(Texture*, Vec2, float);

	/**
	@brief Updates the Internal values (Velocity/Pos)
	@param float - delta time
	*/
	virtual void update(float) = 0;

	Vec2 getVelocity();
	void setVelocity(Vec2 velocity);
	
	float getRotationSpeed();
	void setRotationSpeed(float rotationSpeed);
protected:
	Vec2 velocity;

	float rotationSpeed;
	float maxRotationSpeed;
};