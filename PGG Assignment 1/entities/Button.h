#include <SDL_ttf.h>

#include "Entity.h"

#pragma once

class Button : public Entity
{
public:
	Button(Vec2 pos, Texture* texture, std::string name, TTF_Font* font, SDL_Colour colour, SDL_Renderer* renderer);

	~Button();

	bool isClicked(Vec2 cursor);

	void render();
private:

	std::string name;
	Texture* text;
};