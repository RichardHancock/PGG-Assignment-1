#include <vector>

#include "../Vec2.h"
#include "../Texture.h"
#include "Particle.h"

#pragma once

/**
@brief An interface to create, manage and destroy particles for one emitter
*/
class ParticleSystem
{
public:
	/**
	@brief Creates a Particle System
	
	@param Vec2 - Position of the emitter
	@param std::vector<Texture*> - Array of texture*
	@param int - How many particles are created each tick
	*/
	ParticleSystem(Vec2 emitterPos, std::vector<Texture*> textures, int particlesPerTickRate, Vec2 direction);
	
	/// Clears vectors the particle system created
	~ParticleSystem();

	/**
	@brief Update all particles in the system
	
	Deletes expired particles, and runs update on all particles.
	@param float - Time since last frame
	*/
	void update(float dt);

	/**
	@brief Generate some new particles in the system

	Amount is dictated by the "particlesPerTickRate" passed in through the constructor
	*/
	void generateNewParticles();

	/**
	@brief Draws all particles
	*/
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
	/// Direction to emit particles
	Vec2 direction;
};
