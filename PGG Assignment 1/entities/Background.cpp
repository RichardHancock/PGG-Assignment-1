#include "Background.h"
#include <iostream>

Background::Background(Texture* texture, Vec2 pos, int startingX)
	: Entity(texture, pos), startingX(startingX)
{

}
void Background::update(float dt)
{
	pos.x -= (scrollSpeed * dt);
	if (pos.x < -getDimensions().x) 
	{
		pos.x = (float)startingX;
	}
}