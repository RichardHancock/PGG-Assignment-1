#include "Entity.h"

#pragma once

class Tile : public Entity
{
public:
	Tile(Texture*, Vec2, bool);
	
	void update(float dt);
	bool isCollidable();
	void render(SDL_Rect* camera);
private:
	bool collidable;
};