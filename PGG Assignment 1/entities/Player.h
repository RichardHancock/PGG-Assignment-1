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
	
	/**
	@brief Inflict damage to the player's health
	@param int - Damage amount
	*/
	void hit(int damage);

	/**
	@brief Get the player's current health
	@return int - Player's health
	*/
	int getHealth();

	/**
	@brief Checks if the player is has no health left
	@return bool - True if dead, false if alive
	*/
	bool isDead();

	bool landed;

private:
	void shoot();

	bool isFiring;
	bool movingLeft;
	bool movingRight;
	bool isJumping;
	bool facingRight;
	float delay;

	int health;

	const float gravity = 100.0f;
	const float initialJumpVelocity = -200.0f;

	std::vector<Bullet*> bullets;
	Texture* bulletSprite;
};