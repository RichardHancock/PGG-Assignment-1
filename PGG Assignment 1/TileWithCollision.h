#include "Tile.h"

#pragma once

class TileWithCollision : public Tile
{
public:
	TileWithCollision(Texture*, Vec2);
	
	void update(float dt);
private:

};