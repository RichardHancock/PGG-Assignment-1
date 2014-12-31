#include "Level.h"

Level::Level(std::vector<std::vector<Tile*>> &tiles, Texture* background, int tileCountW, int tileCountH)
	: tiles(tiles), background(background), tileCountW(tileCountW), tileCountH(tileCountH)
	, levelWidth(tileCountW * tileDimensions.x), levelHeight(tileCountH * tileDimensions.y)
{
	/*
	levelWidth = tileCountW * tileDimensions.x;
	levelHeight = tileCountH * tileDimensions.y;
	*/
}

void Level::render(SDL_Rect* camera)
{
	background->draw(Vec2(0, 0));

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