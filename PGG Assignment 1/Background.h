#include "Entity.h"

#pragma once

class Background : public Entity
{
public:
	Background(Texture*, Vec2, int, int);
	void update(float);
private:
	const int SCREEN_HEIGHT;
	const int SCREEN_WIDTH;
	const float scrollSpeed = 50;
};