#include "Bullet.h"

Bullet::Bullet(Texture* inputTexture, Vec2 inputPos, bool facingRight) 
	:EntityWithMotion(inputTexture, inputPos), facingRight(facingRight)
{
	
}

void Bullet::update(float dt)
{	
	pos += velocity * dt;
}

void Bullet::render()
{
	(*sprite).draw(pos, facingRight);
}

