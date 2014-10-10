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
	return (texture ? true : false);
}

void Texture::draw(Vec2 pos)
{
	// Ok, now we want to draw our texture to the screen
	// First we're going to declare an SDL_Rect which we will use for specifying where in the window it should be drawn and how big it should be
	// We will ultimately do a memory copy from our texture to the window and traditionally we say we are copying from a 'source' to a 'destination'
	// This rectangle will specify the destination parameters for us
	SDL_Rect destRect;
	// SDL has (0,0) at the top left corner - check this by playing about with the numbers!
	destRect.x = pos.x;
	destRect.y = pos.y;

	// Query the texture to get its original width and height
	SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);

	// Here we are telling the renderer to copy the texture memory to our screen,
	// at the position of the rectangle we specify
	SDL_RenderCopy(currentRenderer, texture, NULL, &destRect);
}

SDL_Renderer* Texture::getRenderer()
{
	return currentRenderer;
}
