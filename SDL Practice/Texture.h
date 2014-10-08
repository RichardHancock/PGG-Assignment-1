#include <SDL.h>
#include <string>

class Texture
{
public:
	Texture(std::string, SDL_Renderer*);
	~Texture();

	void Texture::draw(SDL_Renderer*);
	bool Texture::load(std::string, SDL_Renderer*);

private:
	SDL_Texture* texture;

	bool Texture::createTexture(SDL_Surface&, SDL_Renderer*);

	
};