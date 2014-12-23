#include "Bullet.h"
#include <iostream>

Bullet::Bullet(Texture* inputTexture, Vec2 inputPos) 
	:Entity(inputTexture, inputPos)
{
	speed = 10;
}

Bullet::~Bullet()
{

}

void Bullet::update(float dt)
{	
	pos.y -= speed;
}

