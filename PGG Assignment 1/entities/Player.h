#include <vector>

#include "EntityWithMotion.h"
#include "Bullet.h"

#pragma once

/**
@class Player
@brief The Player, his physics, input handling and bullets(Abandoned)
*/
class Player : public EntityWithMotion
{
public:

	/**
	@brief Creates the Player
	@param Texture* - Players's sprite
	@param Vec2 - Starting position
	@param Texture* - Bullet's sprite
	*/
	Player(Texture*, Vec2, Texture*);

	~Player();

	/**
	@brief Render player's sprite at its position
	*/
	void render();

	/**
	@brief Updates the velocities of the player.
	
	This is so that collision detection knows where the player will be next and prevent collision.
	@param float - delta time
	*/
	void updateVelocities(float dt);

	/**
	@brief Updates the Internal values (Velocity/Pos)
	@param float - delta time
	*/
	void update(float);

	/**
	@brief Processes any Keyboard input relevant to the Player (Moving Left/right/spacebar)
	@param SDL_Event - The Event Data
	*/
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

	/**
	A publicly accessible bool that the collision detection uses to see if the player has landed
	@todo There is probably a better way to do this, but I have given up on the collision for now.
	*/
	bool landed;

private:
	/**
	@brief Fire a bullet
	*/
	void shoot();

	/// All the bullets owned by the player
	std::vector<Bullet*> bullets;

	/// Is the player firing currently
	bool isFiring;

	/// Is the player moving left
	bool movingLeft;

	/// Is the player moving right
	bool movingRight;

	/// Is the player jumping
	bool isJumping;

	/// Should the sprite be flipped because the player is traveling a different direction
	bool facingRight;

	/**
	Time left in delay between firing the gun
	@todo Replace with the Timer Class
	*/
	float delay;

	/// Player's Health
	int health;

	/// The force of gravity
	const float gravity = 100.0f;

	/// Player's max jump speed
	const float initialJumpVelocity = -150.0f;

	/// The Bullet's sprite
	Texture* bulletSprite;
};