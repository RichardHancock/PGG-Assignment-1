#include "Tile.h"

Tile::Tile(Texture* texture, Vec2 pos, bool collidable)
	: Entity(texture, pos), collidable(collidable)
{

}

void Tile::update(float dt)
{
	//No Function but required since the base class has it.
}

void Tile::render(SDL_Rect* camera)
{
	//Performs a check if the tile is inside the camera, if it isn't it won't be drawn.
	SDL_Rect tileRect;
	tileRect.x = (int)pos.x;
	tileRect.y = (int)pos.y;
	tileRect.w = getDimensions().x;
	tileRect.h = getDimensions().y;

	if (SDL_HasIntersection(camera, &tileRect))
	{
		Vec2 offsetPos;
		offsetPos.x = pos.x - camera->x;
		offsetPos.y = pos.y - camera->y;
		(*sprite).draw(offsetPos, rotation);
	}
	
}

bool Tile::isCollidable()
{
	return collidable;
}