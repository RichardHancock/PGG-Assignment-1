#include <SDL.h>
#include <string>
#include "Vec2.h"

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
	Texture(std::string, SDL_Renderer*);
	~Texture();

	void Texture::draw(Vec2);
	bool Texture::load(std::string, SDL_Renderer*);
	SDL_Renderer* Texture::getRenderer();
private:
	SDL_Texture* texture;
	SDL_Renderer* currentRenderer;
	bool Texture::createTexture(SDL_Surface&);
};

#endif