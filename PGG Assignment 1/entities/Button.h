#include <SDL_ttf.h>

#include "Entity.h"

#pragma once

class Button : public Entity
{
public:
	Button(Vec2 pos, Texture* texture, std::string name, TTF_Font* font, SDL_Colour colour, SDL_Renderer* renderer);

	~Button();

	bool isClicked(Vec2 cursor);

	/**
	@brief Updates the Internal values (Velocity/Pos)
	@param float - delta time
	*/
	void update(float dt);

	/**
	@brief Render button at its position
	*/
	void render();
private:

	//Almost gave the buttons function pointers to execute when clicked, but I decided to play it safe.
	//as i'm not sure as to how they work or any performance considerations.

	///String that appears in the Box
	std::string name;
	
	///Texture containing the rendered text
	Texture* text;
};