#include <map>
#include <vector>

#include "Tile.h"
#include "Level.h"

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
	

	bool loadFile(std::string filename, SDL_Renderer* renderer);

	Level* getLevel(std::string name);

private:
	const Vec2 TILE_DIMENSIONS = { 32, 32 };

	std::map<std::string, Level*> levels;

	void createTileVector(std::vector<std::vector<Tile*>> &tiles, int levelHeight, int levelWidth);

	Tile* createTile(std::map<TileType, TileProperties> &textures, std::ifstream &file, Vec2 gridPos);

	std::map<TileType, TileProperties> loadTileTextures(SDL_Renderer* renderer, std::ifstream &file);

};