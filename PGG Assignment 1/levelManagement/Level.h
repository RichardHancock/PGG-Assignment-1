#pragma once

#include <vector>

#include "Tile.h"
#include "../entities/Background.h"

/**
@class Level
@brief Class containing all the Tiles for a level
*/
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
	
	/**
	@brief Render Tiles relative to passed in camera
	@param SDL_Rect* - The current camera
	*/
	void render(SDL_Rect* screen);

	/**
	@brief Updates the internal values of all Tiles
	@param float - delta time
	*/
	void update(float dt);

	/**
	@brief Get all tiles inside the passed in rectangle
	@param SDL_Rect - The box stating what area, the tiles should be from 
	@return std::vector<Tile*> - Vector of all tiles inside the catchment box
	*/
	std::vector<Tile*> checkTiles(SDL_Rect);

	/**
	@brief Get the position the Player should start at
	@return Vec2 - Start Position
	*/
	Vec2 getStartPos() { return start->getPos() - Vec2(0, 50.0f); }

	/**
	@brief Get the box area the Player needs to reach to win
	@return SDL_Rect - The Finishing Area
	*/
	SDL_Rect getEndBox() { return end->getAABB(); }

private:
	///Vector of all tiles in the level
	std::vector<std::vector<Tile*>> tiles;

	///The start tile
	Tile* start;

	///The end tile
	Tile* end;

	///Background sliding loop of images 
	std::vector<Background*> backgroundLoop;

	/**
	@brief Create a loop of background images
	@param std::vector<Texture*> - Vector containing all the texture to be used in the loop
	*/
	void createBackgroundLoop(std::vector<Texture*> backgrounds);

	///The Dimension of all tiles
	const Vec2 tileDimensions = { 32, 32 };

	///Tile count in the x axis (Width)
	const int tileCountW;

	///Tile count in the y axis (Height)
	const int tileCountH;

	///Level's width in pixels
	const int levelWidth;

	///Level's height in pixels
	const int levelHeight;
};
