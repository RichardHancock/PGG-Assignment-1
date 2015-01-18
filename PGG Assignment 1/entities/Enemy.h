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
	@param int - Damage Capability
	*/
	Enemy(Texture*, Vec2, int);

	/**
	@brief Updates internal value
	@param float - delta time
	*/
	virtual void update(float dt) = 0;

	/**
	@brief Render the enemy
	@param SDL_Rect* - Global camera position to render relative to
	*/
	virtual void render(SDL_Rect* camera);
private:
	int health;

	const int damage;
};