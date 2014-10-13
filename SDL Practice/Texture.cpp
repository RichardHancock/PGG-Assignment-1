#include "Texture.h"
#include <iostream>

Texture::Texture(std::string filename, SDL_Renderer* renderer)
{	
	load(filename, renderer);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

bool Texture::load(std::string filename, SDL_Renderer* renderer)
{
	SDL_Surface *image = SDL_LoadBMP(filename.c_str());
	if (!image)
	{
		// We'll do a quick check here because it's easy to get filenames or directories wrong
		std::cout << "Can't find image named" << filename << std::endl;
		return false;
	}

	currentRenderer = renderer;
	Texture::createTexture(*image); //Need error check here
	SDL_FreeSurface(image);
	return true;
}

bool Texture::createTexture(SDL_Surface &image)
{
	texture = SDL_CreateTextureFromSurface(currentRenderer, &image);
	SDL_QueryTexture(texture, NULL, NULL, &dimensions.x, &dimensions.y);
	return (texture ? true : false);
}

void Texture::draw(Vec2 pos)
{
	SDL_Rect destRect;

	destRect.x = pos.x;
	destRect.y = pos.y;

	// Query the texture to get its original width and height
	destRect.w = dimensions.x;
	destRect.h = dimensions.y;

	// Here we are telling the renderer to copy the texture memory to our screen,
	// at the position of the rectangle we specify
	SDL_RenderCopy(currentRenderer, texture, NULL, &destRect);
}

Vec2 Texture::getDimensions()
{
	return dimensions;
}

SDL_Renderer* Texture::getRenderer()
{
	return currentRenderer;
}
