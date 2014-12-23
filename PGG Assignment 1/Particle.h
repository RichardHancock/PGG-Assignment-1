#include "EntityWithMotion.h"
#include "Utility.h"

#pragma once

class Particle : EntityWithMotion
{
public:
	Particle(Texture*,Vec2,Colour,float);
	~Particle();
	
	void update(float);
private:
	Colour colour;
	float lifespan;
};