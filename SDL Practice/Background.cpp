#include "Background.h"
#include <iostream>

Background::Background(Texture* texture, Vec2 pos, int SCREEN_HEIGHT, int SCREEN_WIDTH)
	: Entity(texture, pos), SCREEN_HEIGHT(SCREEN_HEIGHT), SCREEN_WIDTH(SCREEN_WIDTH)
{

}
void Background::update(float dt)
{
	int offset = 3; //This covers a slight rounding error that occurs

	pos.y += (scrollSpeed * dt);
	if (pos.y >= SCREEN_HEIGHT - offset) 
	{
		pos.y = (float)-SCREEN_HEIGHT;
	}
}