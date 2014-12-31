#include "Entity.h"

#pragma once

class Tile : public Entity
{
public:
	Tile(Texture*, Vec2);
	
	void update(float dt);

	void render(SDL_Rect* camera);
private:
	
};