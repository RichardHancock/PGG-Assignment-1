#include "EntityWithMotion.h"
#include "Utility.h"

#pragma once

class Particle : public EntityWithMotion
{
public:
	/**
	@brief Create a Particle
	
	@param Texture* - Pointer to texture for the particle to display
	@param Vec2 - Particles position
	@param float - The maximum velocity
	@param float - The maximum rotation speed
	@param Colour - Colour/Tint to apply (UNTESTED)
	@param float - Lifespan of the particle (Almost in seconds)
	*/
	Particle(Texture*,Vec2,float,float,Colour,float);
	
	/**
	@brief Updates a Particle
	
	@param
	*/
	void update(float);

	bool hasExpired();

private:
	Colour colour;
	float lifespan;
};