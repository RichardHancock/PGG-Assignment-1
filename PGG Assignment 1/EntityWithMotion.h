#include "Entity.h"

#pragma once

class EntityWithMotion : Entity
{
public:
	EntityWithMotion();
	virtual void update(float) = 0;

	Vec2 getVelocity() { return velocity; }
	
	void setVelocity(Vec2 newVelocity) 
	{ 
		velocity = newVelocity; 
	}

	
	
protected:
	Vec2 velocity;
	float maxVelocity;

	float rotationSpeed;
	float maxRotationSpeed;
};