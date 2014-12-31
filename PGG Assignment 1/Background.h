#include "Entity.h"

#pragma once

class Background : public Entity
{
public:
	Background(Texture*, Vec2, int);
	void update(float);
private:
	const float scrollSpeed = 50;
	const int startingX;
};