#include "Entity.h"

#pragma once

/**
@class Background
@brief A background image used in a scrolling background set
*/
class Background : public Entity
{
public:
	/**
	@brief Create a background
	@param Texture* - Background sprite
	@param Vec2 - Background starting position
	@param int - X Position for where the background will move back to after scrolling once
	*/
	Background(Texture*, Vec2, int);

	/**
	@brief Updates the Internal values (Velocity/Pos)
	@param float - delta time
	*/
	void update(float);
private:
	/// Speed the background will scroll
	const float scrollSpeed = 25;

	///X Position for where the background will move back to after scrolling once
	const int startingX;
};