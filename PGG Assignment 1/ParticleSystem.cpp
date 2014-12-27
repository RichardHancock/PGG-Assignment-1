#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Vec2 emitterPos, std::vector<Texture*> textures, int particlesPerTickRate) 
	: emitterPos(emitterPos), textures(textures), particlesPerTickRate(particlesPerTickRate)
{
	
}

void ParticleSystem::update(float dt)
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].update(dt);
	}

	//Maybe put generateNewParticles here but might be better to have for external calls only
}

void ParticleSystem::generateNewParticles()
{
	Particle particle(textures[0], Vec2(200,200), 10, 10, Colour(1,1,1), 100);
	particles.push_back(particle);
}