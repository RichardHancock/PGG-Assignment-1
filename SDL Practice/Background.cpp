#include "Background.h"

Background::Background(Texture* texture, Vec2 pos, int SCREEN_HEIGHT, int SCREEN_WIDTH)
	: Entity(texture, pos), SCREEN_HEIGHT(SCREEN_HEIGHT), SCREEN_WIDTH(SCREEN_WIDTH)
{

}
void Background::update(float dt)
{
	pos.y += 1 * dt;
	if (pos.y >= 480) {
		pos.y = -480;
	}
}