#include "Background.h"
#include <iostream>

Background::Background(Texture* texture, Vec2 pos, int startingX)
	: Entity(texture, pos), startingX(startingX)
{

}
void Background::update(float dt)
{
	int offset = 3; //This covers a slight rounding error that occurs

	pos.x -= (scrollSpeed * dt);
	if (pos.x < 0 - offset) 
	{
		pos.x = (float)startingX;
	}
}