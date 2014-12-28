#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Vec2 emitterPos, std::vector<Texture*> textures, int particlesPerTickRate) 
	: emitterPos(emitterPos), textures(textures), particlesPerTickRate(particlesPerTickRate)
{
	
}

ParticleSystem::~ParticleSystem()
{
	particles.clear();
	textures.clear();
}

void ParticleSystem::update(float dt)
{
	std::vector<int> particlesToErase;
	
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		particles[i].update(dt);

		// Check if the particle has exceeded its lifespan
		if (particles[i].hasExpired())
		{
			// Add the particle to a vector as deleting it in this loop would get messy.
			particlesToErase.push_back(i);
		}
	}

	// Now delete the destroyed particles
	for (unsigned int i = 0; i < particlesToErase.size(); i++)
	{
		particles.erase(particles.begin() + particlesToErase[i]);
	}

	particlesToErase.clear();



	//Maybe put generateNewParticles here but might be better to have for external calls only
}

void ParticleSystem::render()
{
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		particles[i].render();
	}
}

void ParticleSystem::generateNewParticles()
{
	Particle particle(textures[0], Vec2(200,200), 10, 10, Colour(1,1,1), 10);
	particles.push_back(particle);
}