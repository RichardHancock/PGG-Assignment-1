#include "Entity.h"

#ifndef BULLET_H
#define BULLET_H


class Bullet: public Entity
{
public:
	Bullet(Texture*, Vec2);
	~Bullet();
	void Bullet::update(float);
protected:
	
private:
	int speed;
	char direction;
};

#endif
