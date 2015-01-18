#pragma once

#include <vector>

#include "Tile.h"
#include "../entities/Background.h"

class Level
{
public:
	/**
	@brief Contains a Level and pointers to its data, also holds method to access this data
	in a meaningful way.
	
	@param std::vector<std::vector<Tile*>>& - Reference to all the tiles.
	@param std::vector<Texture*> - Background images to be used in scrolling background.
	@param int - Amount of tiles in the X axis (Width).
	@param int - Amount of tiles in the Y axis (Height)/
	@param std::vector<Tile*> - Any tiles that have a special significance. 
		Order: startTile, endTile
	*/
	Level(std::vector<std::vector<Tile*>>&, std::vector<Texture*>, int, int, std::vector<Tile*>);
	
	void render(SDL_Rect* screen);

	void update(float dt);

	std::vector<Tile*> checkTiles(SDL_Rect);

	Vec2 getStartPos() { return start->getPos() - Vec2(0, 50.0f); }
	SDL_Rect getEndBox() { return end->getAABB(); }

private:
	std::vector<std::vector<Tile*>> tiles;

	Tile* start;
	Tile* end;

	std::vector<Background*> backgroundLoop;

	void createBackgroundLoop(std::vector<Texture*> backgrounds);
	const Vec2 tileDimensions = { 32, 32 };
	const int tileCountW;
	const int tileCountH;
	const int levelWidth;
	const int levelHeight;
};
