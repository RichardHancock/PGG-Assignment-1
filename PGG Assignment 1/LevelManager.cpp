#include <fstream>
#include <string>

#include "LevelManager.h"
#include "Utility.h"

LevelManager::LevelManager(std::string filename, SDL_Renderer* renderer)
{
	loadFile(filename, renderer);
}

bool LevelManager::loadFile(std::string filename, SDL_Renderer* renderer)
{
	std::ifstream levelFile;
	levelFile.open(filename.c_str(), std::fstream::in);
	if (!levelFile.is_open())
	{
		Utility::log(Utility::E, filename + "failed to load");
		return false;
	}

	int levelHeight, levelWidth;
	std::string bgfilename;
	levelFile >> levelHeight;
	levelFile >> levelWidth;
	levelFile >> bgfilename;
	Texture* background = new Texture(bgfilename, renderer);

	//Load all tile textures
	std::map<TileType, TileProperties> tileProperties;
	tileProperties = loadTileTextures(renderer, levelFile);

	//Load tile data
	std::vector<Tile*> tiles;

	for (int h = 0; h < levelHeight; h++)
	{
		for (int w = 0; w < levelWidth; w++)
		{
			createTile(tileProperties, levelFile, Vec2(w,h));
		}
	}
	
	return true;
}

std::map<LevelManager::TileType, LevelManager::TileProperties> LevelManager::loadTileTextures(
	SDL_Renderer* renderer, std::ifstream &file)
{
	std::map<TileType, TileProperties> tileProperties;

	int tilePropertiesCount;
	file >> tilePropertiesCount;

	for (int i = 0; i < tilePropertiesCount; i++)
	{
		TileProperties currentTileProperties;
		//Type of tile that uses this texture
		int type;
		file >> type;
		//Force the int to a TileType enum
		TileType tileType = (TileType)type;
		
		//Texture
		Texture* texture = NULL;
		std::string textureFilename;
		file >> textureFilename;
		//If a path was provided, load texture
		if (textureFilename != "0")
		{
			Texture* texture = new Texture(textureFilename, renderer);
		}
		
		currentTileProperties.texture = texture;

		//Collision
		int collisionInt;
		file >> collisionInt;
		//Convert to a boolean - 0 is false, anything else is true
		currentTileProperties.hasCollision = (collisionInt != 0);

		//textures.push_back(currentTexture);
		tileProperties[tileType] = currentTileProperties;
	}

	return tileProperties;
}

Tile* LevelManager::createTile(std::map<TileType, TileProperties> &tileProperties, std::ifstream &file, Vec2 gridPos)
{
	TileType currentTile;
	// Might be a more elegant solution to this type juggling, but it works fine for now.
	int tempCurrentTile;
	file >> tempCurrentTile;
	currentTile = (TileType)tempCurrentTile;

	//Time/space saver
	TileProperties properties = tileProperties[currentTile];

	//If the tile has no texture don't create a tile.
	if (properties.texture == NULL)
	{
		return NULL;
	}

	//GridPos calculation (Might need + 1)
	gridPos *= TILE_DIMENSIONS;
	
	Tile* tile;
	
	if (properties.hasCollision)
	{
		tile = new TileWithCollision(properties.texture, gridPos);
	}
	else
	{
		tile = new Tile(properties.texture, gridPos);
	}
	

	/*
	switch (currentTile)
	{
	
	case block:
		
		break;
	case start:
	case finish:

	default:
		// An invalid tileType was provided
		Utility::log(Utility::E, "Invalid Tile Type specified " + std::to_string(tempCurrentTile));
		return NULL;
		break;
	}
	*/
}