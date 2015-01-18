#pragma once

#include "EntityWithMotion.h"

/**
@class Enemy

@brief Abstract Class that represents a Enemy
*/
class Enemy : public EntityWithMotion
{
public:
	/**
	@brief Enemy Constructor
	@param Texture* - Sprite
	@param Vec2 - Starting position
	@param int - Enemy health
	@param int - Damage Capability
	*/
	Enemy(Texture*, Vec2, int, int);

	/**
	@brief Updates internal values
	@param float - delta time
	*/
	virtual void update(float dt) = 0;

	/**
	@brief Render the enemy
	@param SDL_Rect* - Global camera position to render relative to
	*/
	virtual void render(SDL_Rect* camera);

	/**
	@brief Checks if the enemy is has no health left
	@return bool - True if dead, false if alive
	*/
	bool isDead();

	/**
	@brief Inflict damage to the enemy's health
	@param int - Damage amount
	*/
	void hit(int damage);

	/**
	@brief Get the enemy's damage value
	@return int - Damage the enemy will deal 
	*/
	int damageAmount();
protected:
	///Current health of the Enemy
	int health;

	///Damage potential of the Enemy
	const int damage;
};