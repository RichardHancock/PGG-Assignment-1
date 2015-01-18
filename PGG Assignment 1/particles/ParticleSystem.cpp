#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Vec2 emitterPos, std::vector<Texture*> textures, int particlesPerTickRate, Vec2 direction
	, Colour min, Colour max)
	: emitterPos(emitterPos), textures(textures), particlesPerTickRate(particlesPerTickRate), direction(direction)
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
		particles.erase(particles.begin() + (particlesToErase[i] - i));
	}

	particlesToErase.clear();
	//Maybe put generateNewParticles here but might be better to have for external calls only
}

void ParticleSystem::render(SDL_Rect* camera)
{
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		particles[i].render(camera);
	}
}

void ParticleSystem::generateNewParticles()
{
	for (int i = 0; i < particlesPerTickRate; i++)
	{
		Particle particle(textures[0], emitterPos, 10, Colour(Utility::randomInt(0, 255),
			Utility::randomInt(0, 255), Utility::randomInt(0, 255)), 3);
		Vec2 randomVelocity;
		randomVelocity.x = Utility::randomFloat(direction.x - 1, direction.x + 1);
		randomVelocity.y = Utility::randomFloat(direction.y - 1, direction.y + 1);
		
		particle.setVelocity(randomVelocity);
		particles.push_back(particle);
	}
}