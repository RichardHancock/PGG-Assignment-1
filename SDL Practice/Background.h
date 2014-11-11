#include "Entity.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background : public Entity
{
public:
	Background(Texture*, Vec2, int, int);
	void update(float);
private:
	const int SCREEN_HEIGHT;
	const int SCREEN_WIDTH;
};

#endif