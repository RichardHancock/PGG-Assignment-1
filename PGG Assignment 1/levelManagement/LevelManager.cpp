#include <fstream>
#include <string>

#include "LevelManager.h"
#include "../Utility.h"

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
	//Get level name
	std::string levelID;
	getline(levelFile, levelID);

	int levelHeight, levelWidth;
	
	levelFile >> levelHeight;
	levelFile >> levelWidth;

	int bgCount;
	levelFile >> bgCount;
	std::vector<Texture*> backgrounds;
	for (int i = 0; i < bgCount; i++)
	{
		std::string bgfilename;
		levelFile >> bgfilename;
		Texture* background = new Texture(bgfilename, renderer);

		backgrounds.push_back(background);
	}

	//Load all tile textures
	std::map<TileType, TileProperties> tileProperties;
	tileProperties = loadTileTextures(renderer, levelFile);
	TileProperties debuging = tileProperties[block];
	//Load tile data
	//Create a multidimensional vector
	std::vector<std::vector<Tile*>> tiles;
	createTileVector(tiles, levelHeight, levelWidth);

	for (int h = 0; h < levelHeight; h++)
	{
		for (int w = 0; w < levelWidth; w++)
		{
			tiles[w][h] = createTile(tileProperties, levelFile, Vec2((float)w,(float)h));
		}
	}
	
	//Create level from the loaded data
	Level* level;
	level = new Level(tiles, backgrounds, levelWidth, levelHeight);

	levels[levelID] = level;

	return true;
}

Level* LevelManager::getLevel(std::string name) 
{
	return levels[name];
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
		Texture* texture;
		std::string textureFilename;
		file >> textureFilename;
		//If a path was provided, load texture
		if (textureFilename != "0")
		{
			texture = new Texture(textureFilename, renderer);
		}
		else
		{
			texture = NULL;
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
	
	Tile* tile = new Tile(properties.texture, gridPos, properties.hasCollision);
	
	return tile;
}

void LevelManager::createTileVector(std::vector<std::vector<Tile*>> &tiles, int levelHeight, int levelWidth)
{
	tiles.resize(levelWidth);
	for (int x = 0; x < levelWidth; x++)
	{
		tiles[x].resize(levelHeight);
	}
}