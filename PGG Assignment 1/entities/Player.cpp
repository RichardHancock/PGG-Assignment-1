#include "Player.h"

Player::Player(Texture* texture, Vec2 pos, Texture*bulletTexture, float maxVelocity)
	:EntityWithMotion(texture, pos, maxVelocity, 0), bulletSprite(bulletTexture)
{
	delay = 0;
	movingLeft = false;
	movingRight = false;
	isFiring = false;
	isJumping = false;
	facingRight = true;
	landed = true;
}

Player::~Player()
{
	bullets.clear();
}

void Player::eventKeyboard(SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_a:
			movingLeft = true;
			facingRight = false;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			movingRight = true;
			facingRight = true;
			break;
		case SDLK_UP:
		case SDLK_w:
			if (!isJumping)
			{
				isJumping = true;
				velocity.y = initialJumpVelocity;
			}
			break;
		case SDLK_SPACE:
			isFiring = true;
			break;
		}
		break;
	
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_a:
			movingLeft = false;
			break;

		case SDLK_RIGHT:
		case SDLK_d:
			movingRight = false;
			break;

		case SDLK_SPACE:
			isFiring = false;
			break;
		}
	}
}

void Player::updateVelocities(float dt)
{
	velocity.x = 0;

	if (movingLeft &!movingRight)
	{
		// We are told to move left
		velocity.x = -200.0f;
	}
	if (movingRight &!movingLeft)
	{
		// We are told to move right
		velocity.x = 200.0f;
	}

	if (!landed)
	{
		velocity.y += gravity * dt;
	}
	
}

void Player::update(float dt)
{	
	if (isFiring && delay > 0.75) { shoot(); }
	delay += 1 * dt;

	move(Vec2((velocity.x * dt), velocity.y * dt));

	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update(dt);
	}

}

void Player::render()
{
	//Render Bullets
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->render();
		if (bullets[i]->getPos().y < -30)
		{
			bullets.erase(bullets.begin() + i);
		}
	}

	//Render Player
	(*sprite).draw(Vec2(0,pos.y),facingRight);
}

void Player::shoot()
{
	Vec2 bulletLineup = pos;
	bulletLineup.x = 0;
	bulletLineup.y += (getDimensions().y / 2) - (bulletSprite->getDimensions().y / 2);
	
	Bullet* bullet = new Bullet(bulletSprite, bulletLineup, facingRight);
	float velocityX = facingRight ? 500.0f : -500.0f;
	bullet->setVelocity(Vec2(velocityX, 0));
	bullets.push_back(bullet);
	delay = 0;
}