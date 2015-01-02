#include "EntityWithMotion.h"

#pragma once

class Bullet: public EntityWithMotion
{
public:
	Bullet(Texture*, Vec2, bool);
	
	void update(float);
	void render();
private:
	bool facingRight;
};
