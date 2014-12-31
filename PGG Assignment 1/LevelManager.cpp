#include <fstream>
#include <string>

#include "LevelManager.h"
#include "Utility.h"

LevelManager::LevelManager(std::string filename, SDL_Renderer* renderer)
{
	loadFile(filename, renderer);
}

struct wouldntNeedThisInPython //Never thought I would miss dictionary types
{
	//Because STL map
	//bool operator()(const char* s1)
};

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
	//std::vector<TileTexture> textures;
	std::map<TileType, Texture*> textures;
	int tileTextureCount;
	levelFile >> tileTextureCount;

	for (int i = 0; i < tileTextureCount; i++)
	{
		
		//Type of tile that uses this texture
		TileTexture currentTexture;
		int type;
		levelFile >> type;
		currentTexture.type = (TileType)type;


		//Texture
		std::string textureFilename;
		levelFile >> textureFilename;
		Texture* texture = new Texture(textureFilename, renderer);
		currentTexture.texture = texture;

		//textures.push_back(currentTexture);
		textures[(TileType)type] = texture;
	}


	//Load tile data
	std::vector<Tile*> tiles;

	for (int h = 0; h < levelHeight; h++)
	{
		for (int w = 0; w < levelWidth; w++)
		{
			createTile(textures, levelFile, Vec2(w,h));
		}
	}
	
	return true;
}

Tile* LevelManager::createTile(std::map<TileType, Texture*> &textures, std::ifstream &file, Vec2 gridPos)
{
	TileType currentTile;
	// Might be a more elegant solution to this type juggling, but it works fine for now.
	int tempCurrentTile;
	file >> tempCurrentTile;
	currentTile = (TileType)tempCurrentTile;

	//GridPos calculation (Might need + 1)
	gridPos *= TILE_DIMENSIONS;
	
	Tile* tile;

	switch (currentTile)
	{
	case blank:
		tile = new Tile(NULL, gridPos);
		break;
	case block:
		tile = new Tile(textures[currentTile], gridPos);
		break;
	case start:
	case finish:

	default:
		// An invalid tileType was provided
		Utility::log(Utility::E, "Invalid Tile Type specified " + std::to_string(tempCurrentTile));
		return NULL;
		break;
	}
}