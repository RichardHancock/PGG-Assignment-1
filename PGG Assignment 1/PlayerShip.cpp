#include "PlayerShip.h"

PlayerShip::PlayerShip(Texture* texture, Vec2 pos, Texture*bulletTexture)
	:Ship(texture, pos), bulletSprite(bulletTexture)
{
	delay = 0;
	movingLeft = false;
	movingRight = false;
	mouse = { 0, 0 };
	mouseEnabled = false;
	isFiring = false;
}

PlayerShip::~PlayerShip()
{
	bullets.clear();
}


void PlayerShip::eventHandler(SDL_Event &e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEMOTION:
		eventMouse(e);
		break;
	
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		eventKeyboard(e);
		break;
	}
}

void PlayerShip::eventKeyboard(SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
		case SDLK_a:
			movingLeft = true;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			movingRight = true;
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

		case SDLK_q:
			mouseEnabled = !mouseEnabled;
			break;
		}
	}
}

void PlayerShip::eventMouse(SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button) {
		case SDL_BUTTON_LEFT:
			isFiring = true;
			break;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		switch (e.button.button) {
		case SDL_BUTTON_LEFT:
			isFiring = false;
			break;
		}
		break;

	}
}

void PlayerShip::update(float dt)
{
	float velocityX = 0;

	if (movingLeft &!movingRight)
	{
		// We are told to move left
		velocityX = -200.0f;
	}
	if (movingRight &!movingLeft)
	{
		// We are told to move right
		velocityX = 200.0f;
	}
	
	if (mouseEnabled)
	{
		int mouseOffsetLeft = (int)(pos.x + (getDimensions().x / 2)) - 20;
		int mouseOffsetRight = mouseOffsetLeft + 40;

		if (mouse.x < mouseOffsetLeft)
		{
			velocityX = -200.0f;
		}
		if (mouse.x > mouseOffsetRight)
		{
			velocityX = 200.0f;
		}
	}
	
	
	if (isFiring && delay > 10) { shoot(); }
	delay++;

	move(Vec2((velocityX * dt), 0));

	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update(dt);
	}


}

void PlayerShip::render()
{
	(*sprite).draw(pos);

	//Render Bullets
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->render();
		if (bullets[i]->getPos().y < -30)
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

void PlayerShip::shoot()
{
	Vec2 bulletLineup = pos;
	bulletLineup.x += (getDimensions().x / 2) - (bulletSprite->getDimensions().x / 2);
	bullets.push_back(new Bullet(bulletSprite, bulletLineup));
	delay = 0;
}

bool PlayerShip::isMouseEnabled() { return mouseEnabled; }

void PlayerShip::updateMouse(Vec2 oldMouse) { mouse = oldMouse; }