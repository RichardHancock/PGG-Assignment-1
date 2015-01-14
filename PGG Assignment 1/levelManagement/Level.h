#include <vector>

#include "Tile.h"
#include "../entities/Background.h"

#pragma once

class Level
{
public:
	Level(std::vector<std::vector<Tile*>> &tiles, std::vector<Texture*> background, int tileCountW, int tileCountH);
	
	void render(SDL_Rect* screen);

	void update(float dt);

	std::vector<Tile*> checkTiles(SDL_Rect);

private:
	std::vector<std::vector<Tile*>> tiles;

	std::vector<Background*> backgroundLoop;

	void createBackgroundLoop(std::vector<Texture*> backgrounds);
	const Vec2 tileDimensions = { 32, 32 };
	const int tileCountW;
	const int tileCountH;
	const int levelWidth;
	const int levelHeight;
};