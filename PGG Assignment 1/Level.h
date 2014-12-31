#include <vector>

#include "Tile.h"

#pragma once

class Level
{
public:
	Level();
	~Level();
	
private:
	std::vector<std::vector<Tile>> tiles;
	std::vector<Texture*> textures;
};
