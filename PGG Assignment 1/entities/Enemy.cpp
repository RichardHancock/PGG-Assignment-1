#include "Enemy.h"

Enemy::Enemy(Texture* sprite, Vec2 pos, int damage)
	: EntityWithMotion(sprite, pos), damage(damage)
{

}