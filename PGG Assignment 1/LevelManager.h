#include <map>
#include <vector>

#include "TileWithCollision.h"

#pragma once

/**
@brief Loads level data and relevant images 
*/
class LevelManager
{
private:
	enum TileType
	{
		blank = 0,
		block,
		start,
		finish,
	};

	struct TileProperties
	{
		Texture* texture; //< Can be null for no texture
		bool hasCollision;
	};

public:
	LevelManager(std::string filename, SDL_Renderer* renderer);
	~LevelManager();

	bool loadFile(std::string filename, SDL_Renderer* renderer);

private:
	const Vec2 TILE_DIMENSIONS = { 16, 16 };

	Tile* createTile(std::map<TileType, TileProperties> &textures, std::ifstream &file, Vec2 gridPos);

	std::map<TileType, TileProperties> loadTileTextures(SDL_Renderer* renderer, std::ifstream &file);

};