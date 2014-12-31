#include <vector>

#include "Tile.h"

#pragma once

class Level
{
public:
	Level(std::vector<std::vector<Tile*>> &tiles, Texture* background, int tileCountW, int tileCountH);
	
	void render(SDL_Rect* screen);

	void update(float dt);

private:
	std::vector<std::vector<Tile*>> tiles;

	Texture* background;

	const Vec2 tileDimensions = { 32, 32 };
	const int tileCountW;
	const int tileCountH;
	const int levelWidth;
	const int levelHeight;
};
