#include "Entity.h"

#pragma once

class Ship : public Entity
{
public:
	Ship(Texture*, Vec2);
	virtual void shoot() = 0;
protected:
	float velocityY;
	float velocityX;
private:
};