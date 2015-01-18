#include "EntityWithMotion.h"

#pragma once

/**
@class Bullet
@todo Abandoned Class, only kept in because I might come back to it later.
@brief A bullet fired by the player (Currently no damage or collision)
*/
class Bullet: public EntityWithMotion
{
public:
	Bullet(Texture*, Vec2, bool);
	
	/**
	@brief Updates the Internal values (Velocity/Pos)
	@param float - delta time
	*/
	void update(float);

	/**
	@brief Render bullet's sprite at its position
	*/
	void render();
private:
	///Should the sprite be flipped or not relative to its direction
	bool facingRight;
};
