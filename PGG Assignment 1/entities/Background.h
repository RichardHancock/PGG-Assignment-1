#include "Entity.h"

#pragma once

class Background : public Entity
{
public:
	Background(Texture*, Vec2, int);

	/**
	@brief Updates the Internal values (Velocity/Pos)
	@param float - delta time
	*/
	void update(float);
private:
	const float scrollSpeed = 25;
	const int startingX;
};