#include <vector>

#include "Ship.h"
#include "Bullet.h"

#pragma once

class PlayerShip : public Ship
{
public:
	PlayerShip(Texture*, Vec2, Texture*);
	~PlayerShip();

	void render();
	void update(float);
	void updateMouse(Vec2);
	void eventHandler(SDL_Event&);
	bool isMouseEnabled();
private:
	void shoot();
	void eventMouse(SDL_Event&);
	void eventKeyboard(SDL_Event&);

	bool isFiring;
	bool mouseEnabled;
	Vec2 mouse;
	bool movingLeft;
	bool movingRight;

	int delay;

	std::vector<Bullet*> bullets;
	Texture* bulletSprite;
};