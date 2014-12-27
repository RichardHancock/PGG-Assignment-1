#include <vector>

#include "Vec2.h"
#include "Texture.h"
#include "Particle.h"

#pragma once

class ParticleSystem
{
public:
	ParticleSystem(Vec2 emitterPos, std::vector<Texture*> textures, int particlesPerTickRate);
	~ParticleSystem();

	/**
	@brief Update all particles in the system
	
	@param
	*/
	void update(float dt);
	void generateNewParticles();

private:
	/// Position of the Particle Emitter
	Vec2 emitterPos;
	/// Vector containing all the particles in the system
	std::vector<Particle> particles;
	/// Contains all available textures for the particles to use
	std::vector<Texture*> textures;
	/// How many particles will be created every tick
	int particlesPerTickRate;
};
