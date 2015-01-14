#include "Button.h"

Button::Button(Vec2 pos, Texture* texture, std::string name, TTF_Font* font, SDL_Colour colour, SDL_Renderer* renderer)
	: Entity(texture,pos), name(name)
{
	//Using blended which is the nicest quality but heavy on resources, but as this will never change it won't matter.
	text = new Texture(TTF_RenderUTF8_Blended(font, name.c_str(), colour), renderer);
}

Button::~Button()
{
	delete text;
}

bool Button::isClicked(Vec2 cursor)
{
	SDL_Rect point;
	point.x = (int)cursor.x;
	point.y = (int)cursor.y;
	point.h = 1;
	point.w = 1;

	/* Apparently this is implemented in SDL 2.0.4 but 2.0.3 is the latest stable release.
	if (SDL_PointInRect())
	*/
	
	return SDL_HasIntersection(&point, &AABB) != 0; // Had to put != 0 because it uses SDL_Bool instead of bool (Generates Warning)
}

void Button::update(float dt)
{

}

void Button::render()
{
	(*sprite).draw(pos, rotation);
	
	Vec2 textPos;
	textPos.x = pos.x + ((sprite->getDimensions().x / 2) - (text->getDimensions().x / 2));
	textPos.y = pos.y + ((sprite->getDimensions().y / 2) - (text->getDimensions().y / 2));
	(*text).draw(textPos);
}