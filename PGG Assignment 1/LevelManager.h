#include <map>
#include <vector>

#include "Tile.h"

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

	struct TileTexture
	{
		TileType type;
		Texture* texture;
	};

public:
	LevelManager(std::string filename, SDL_Renderer* renderer);
	~LevelManager();

	bool loadFile(std::string filename, SDL_Renderer* renderer);
	Tile* LevelManager::createTile(std::map<TileType, Texture*> &textures, std::ifstream &file, Vec2 gridPos);

private:
	
	const Vec2 TILE_DIMENSIONS = { 16, 16 };

};