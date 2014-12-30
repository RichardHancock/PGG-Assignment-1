#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Vec2.h"
#include "Utility.h"

#pragma once

class Texture
{
public:
	Texture(std::string, SDL_Renderer*);
	Texture(SDL_Surface*, SDL_Renderer*);
	~Texture();
	Vec2 Texture::getDimensions();
	void Texture::draw(Vec2 pos);
	void Texture::draw(Vec2 pos, float rotation);
	void Texture::draw(Vec2 pos, float rotation, Vec2 pivot);
	bool Texture::load(std::string, SDL_Renderer*);
	bool Texture::load(SDL_Surface*, SDL_Renderer*);
	void Texture::setColourTint(Colour colour);
	SDL_Renderer* Texture::getRenderer();
private:
	Vec2 dimensions;
	SDL_Texture* texture;
	SDL_Renderer* currentRenderer;
	bool Texture::createTexture(SDL_Surface&);
};

