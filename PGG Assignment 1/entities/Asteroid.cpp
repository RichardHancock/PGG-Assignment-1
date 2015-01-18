#include "Asteroid.h"

Asteroid::Asteroid(Texture* sprite, Vec2 pos, int damage, Vec2 velocity, Texture* pTexture)
	: Enemy(sprite, pos, damage)
{
	setVelocity(velocity);


	std::vector<Texture*> pTextures;
	pTextures.push_back(pTexture);
	Vec2 direction = velocity.normalize();
	//Particle colour random range R 200 - 255 G 0 - 80 B 0
	particles = new ParticleSystem(pos, pTextures, 1, direction, Colour(200, 0, 0), Colour(255, 80, 0));
}

void Asteroid::update(float dt)
{
	updateAABB();
	particles->setEmitterPos(Utility::getRectCenter(AABB));
	particles->generateNewParticles();
	particles->update(dt);
	pos += (velocity * dt);
}

void Asteroid::render(SDL_Rect* camera)
{
	particles->render(camera);

	Vec2 offsetPos;
	offsetPos.x = pos.x - camera->x;
	offsetPos.y = pos.y - camera->y;
	sprite->draw(offsetPos, rotation);
}