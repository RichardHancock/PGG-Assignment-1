#include "Entity.h"

#pragma once

class Background : public Entity
{
public:
	Background(Texture*, Vec2, int);
	void update(float);
private:
	const float scrollSpeed = 25;
	const int startingX;
};