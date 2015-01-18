#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Vec2 emitterPos, std::vector<Texture*> textures, int particlesPerCallRate, Vec2 direction
	, Colour min, Colour max)
	: emitterPos(emitterPos), textures(textures), particlesPerCallRate(particlesPerCallRate), direction(direction), min(min), max(max)
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

void ParticleSystem::setEmitterPos(Vec2 newPos)
{
	emitterPos = newPos;
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
	for (int i = 0; i < particlesPerCallRate; i++)
	{
		Colour colour = { 0, 0, 0 };
		colour.r = Utility::randomInt(min.r, max.r);
		colour.g = Utility::randomInt(min.g, max.g);
		colour.b = Utility::randomInt(min.b, max.b);

		Particle particle(textures[0], emitterPos, 10, colour, 2);
		Vec2 randomVelocity;
		randomVelocity.x = Utility::randomFloat(direction.x - 2, direction.x + 2);
		randomVelocity.y = Utility::randomFloat(direction.y - 2, direction.y + 2);
		
		particle.setVelocity(randomVelocity);
		particles.push_back(particle);
	}
}