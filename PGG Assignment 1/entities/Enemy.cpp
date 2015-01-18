#include "Enemy.h"

Enemy::Enemy(Texture* sprite, Vec2 pos, int health, int damage)
	: EntityWithMotion(sprite, pos), damage(damage), health(health)
{

}

void Enemy::render(SDL_Rect* camera)
{
	Vec2 offsetPos;
	offsetPos.x = pos.x - camera->x;
	offsetPos.y = pos.y - camera->y;
	sprite->draw(offsetPos, rotation);
}

bool Enemy::isDead()
{
	return (health <= 0);
}