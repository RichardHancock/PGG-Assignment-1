#include "Level.h"

Level::Level(std::vector<std::vector<Tile*>> &tiles, std::vector<Texture*> backgrounds, int tileCountW, int tileCountH)
	: tiles(tiles), tileCountW(tileCountW), tileCountH(tileCountH), levelWidth(tileCountW * tileDimensions.x)
	, levelHeight(tileCountH * tileDimensions.y)
{
	createBackgroundLoop(backgrounds);
}

void Level::createBackgroundLoop(std::vector<Texture*> backgrounds)
{
	
	
	for (int i = 0; i < backgrounds.size(); i++)
	{
		Vec2 backgroundDimensions = backgrounds[0]->getDimensions();

		int backgroundX = i * backgroundDimensions.x;

		Background* background = new Background(backgrounds[1], Vec2(backgroundX, 0));
	}
	
}

void Level::render(SDL_Rect* camera)
{
	
	for (int i = 0; i < backgroundLoop.size(); i++)
	{
		backgroundLoop[i]->draw(Vec2(0, 0));
	}


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