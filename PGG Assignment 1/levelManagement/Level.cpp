#include "Level.h"

Level::Level(std::vector<std::vector<Tile*>> &tiles, std::vector<Texture*> backgrounds, int tileCountW, int tileCountH, std::vector<Tile*> specialTiles)
	: tiles(tiles), tileCountW(tileCountW), tileCountH(tileCountH), levelWidth(tileCountW * (int)tileDimensions.x)
	, levelHeight(tileCountH * (int)tileDimensions.y)
{
	start = specialTiles[0];
	end = specialTiles[1];

	createBackgroundLoop(backgrounds);
}

void Level::createBackgroundLoop(std::vector<Texture*> backgrounds)
{
	//Get the position that the background should reset to  
	int startingX = (backgrounds.size() - 1) * (int)backgrounds[0]->getDimensions().x;
	
	for (unsigned int i = 0; i < backgrounds.size(); i++)
	{
		Vec2 backgroundDimensions = backgrounds[i]->getDimensions();

		int backgroundX = i * (unsigned int)backgroundDimensions.x;

		Background* background = new Background(backgrounds[i], Vec2((float)backgroundX, 0), startingX);

		backgroundLoop.push_back(background);
	}
	
}

void Level::render(SDL_Rect* camera)
{
	//Render Background
	for (Background* bg : backgroundLoop)
	{
		bg->render();
	}

	//Render Tiles
	for (unsigned int x = 0; x < tiles.size(); x++)
	{
		for (unsigned int y = 0; y < tiles[x].size(); y++)
		{
			if (tiles[x][y] != NULL)
			{
				tiles[x][y]->render(camera);
			}
		}
	}
}

void Level::update(float dt)
{
	//Render Background
	for (Background* bg : backgroundLoop)
	{
		bg->update(dt);
	}

	//Update Tiles
	for (unsigned int x = 0; x < tiles.size(); x++)
	{
		for (unsigned int y = 0; y < tiles[x].size(); y++)
		{
			if (tiles[x][y] != NULL)
			{
				tiles[x][y]->update(dt);
			}
		}
	}
}

std::vector<Tile*> Level::checkTiles(SDL_Rect selection)
{
	//I could write a more complex search with filtering here to reduce the amount but this should be fine.

	int offset = 0; //just to make sure we get them all
	//Start the 
	Vec2 start;
	Vec2 end;
	start.x = (selection.x / tileDimensions.x) - offset;
	end.x = ((selection.x + selection.w) / tileDimensions.x) + offset;
	start.y = (selection.y / tileDimensions.y) - offset;
	end.y = ((selection.y + selection.h) / tileDimensions.y) + offset;

	std::vector<Tile*> results;

	if (start.x < 0) { start.x = 0; }
	if (end.x > tileCountW) { end.x = (float)tileCountW; }
	if (start.y < 0) { start.y = 0; }
	if (end.y > tileCountH) { end.y = (float)tileCountH; }

	for (int x = (int)start.x; x < end.x; x++)
	{
		for (int y = (int)start.y; y < end.y; y++)
		{
			if (tiles[x][y] != NULL)
			{
				if (tiles[x][y]->isCollidable())
				{
					results.push_back(tiles[x][y]);
				}				
			}
			
		}
	}

	return results;
}