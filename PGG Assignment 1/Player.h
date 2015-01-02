#include <vector>

#include "EntityWithMotion.h"
#include "Bullet.h"

#pragma once

class Player : public EntityWithMotion
{
public:
	Player(Texture*, Vec2, Texture*, float);
	~Player();

	void render();
	void update(float);
	void eventKeyboard(SDL_Event&);
	
private:
	void shoot();

	bool isFiring;
	bool movingLeft;
	bool movingRight;
	bool isJumping;
	bool facingRight;

	float delay;

	const float initialJumpVelocity = 20.0f;

	std::vector<Bullet*> bullets;
	Texture* bulletSprite;
};