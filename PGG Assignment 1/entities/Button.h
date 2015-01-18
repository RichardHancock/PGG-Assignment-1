#include <SDL_ttf.h>

#include "Entity.h"

#pragma once
/**
@class Button
@brief Button for use in a menu. Uses a button image and a string to display on it.
*/
class Button : public Entity
{
public:
	/**
	@brief Create a Button
	@param Vec2 - Button's position
	@param Texture* - Background texture
	@param std::string - String to display on the button
	@param TTF_Font* - Font to use for rendering text
	@param SDL_Colour - Colour of the text
	@param SDL_Renderer - The renderer
	*/
	Button(Vec2 pos, Texture* texture, std::string name, TTF_Font* font, SDL_Colour colour, SDL_Renderer* renderer);

	~Button();

	/**
	@brief Checks if the button has been clicked by the cursor
	@param Vec2 - Current cursor position
	@return bool - True if clicked, else false
	*/
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

	/*Almost gave the buttons function pointers to execute when clicked, but I decided to play it safe.
	as I'm not sure as to how they work or any performance considerations.*/

	///String that appears in the Box
	std::string name;
	
	///Texture containing the rendered text
	Texture* text;
};