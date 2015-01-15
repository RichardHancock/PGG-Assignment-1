#pragma once

#include "../entities/Entity.h"

class Tile : public Entity
{
public:
	Tile(Texture*, Vec2, bool, Utility::TileType);
	
	void update(float dt);
	bool isCollidable();
	void render(SDL_Rect* camera);

	Utility::TileType getType();
private:
	bool collidable;
	Utility::TileType type;
};