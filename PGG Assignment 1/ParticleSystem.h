#include <vector>

#include "Vec2.h"
#include "Texture.h"
#include "Particle.h"

#pragma once

class ParticleSystem
{
public:
	/**
	@brief Creates a Particle System
	
	@param Vec2 - Position of the emitter
	@param std::vector<Texture*> - Array of texture*
	@param int - How many particles are created each tick
	*/
	ParticleSystem(Vec2 emitterPos, std::vector<Texture*> textures, int particlesPerTickRate);

	~ParticleSystem();

	/**
	@brief Update all particles in the system
	
	@param
	*/
	void update(float dt);
	void generateNewParticles();
	void render();
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
