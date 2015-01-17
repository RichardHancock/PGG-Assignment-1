#include <vector>

#include "EntityWithMotion.h"
#include "Bullet.h"

#pragma once

class Player : public EntityWithMotion
{
public:
	Player(Texture*, Vec2, Texture*);
	~Player();

	void render();
	void updateVelocities(float dt);
	void update(float);
	void eventKeyboard(SDL_Event&);
	
	bool landed;

private:
	void shoot();

	bool isFiring;
	bool movingLeft;
	bool movingRight;
	bool isJumping;
	bool facingRight;
	float delay;

	const float gravity = 100.0f;
	const float initialJumpVelocity = -200.0f;

	std::vector<Bullet*> bullets;
	Texture* bulletSprite;
};