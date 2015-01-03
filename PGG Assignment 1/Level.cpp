#include "Level.h"

Level::Level(std::vector<std::vector<Tile*>> &tiles, std::vector<Texture*> backgrounds, int tileCountW, int tileCountH)
	: tiles(tiles), tileCountW(tileCountW), tileCountH(tileCountH), levelWidth(tileCountW * tileDimensions.x)
	, levelHeight(tileCountH * tileDimensions.y)
{
	createBackgroundLoop(backgrounds);
}

void Level::createBackgroundLoop(std::vector<Texture*> backgrounds)
{
	//Get the position that the background should reset to  
	int startingX = (backgrounds.size() - 1) * backgrounds[0]->getDimensions().x;
	
	for (int i = 0; i < backgrounds.size(); i++)
	{
		Vec2 backgroundDimensions = backgrounds[i]->getDimensions();

		int backgroundX = i * backgroundDimensions.x;

		Background* background = new Background(backgrounds[i], Vec2(backgroundX, 0), startingX);

		backgroundLoop.push_back(background);
	}
	
}

void Level::render(SDL_Rect* camera)
{
	//Render Background
	for (int i = 0; i < backgroundLoop.size(); i++)
	{
		backgroundLoop[i]->render();
	}

	//Render Tiles
	for (int x = 0; x < tiles.size(); x++)
	{
		for (int y = 0; y < tiles[x].size(); y++)
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
	for (int i = 0; i < backgroundLoop.size(); i++)
	{
		backgroundLoop[i]->update(dt);
	}

	//Update Tiles
	for (int x = 0; x < tiles.size(); x++)
	{
		for (int y = 0; y < tiles[x].size(); y++)
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

	for (int x = start.x; x < end.x; x++)
	{
		for (int y = start.y; y < end.y; y++)
		{
			if (tiles[x][y] != NULL)
			{
				results.push_back(tiles[x][y]);
			}
			
		}
	}

	return results;
}