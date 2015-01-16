#pragma once

#include <SDL_mixer.h>
#include <string>

class Audio
{
public:
	Audio(std::string);

	virtual void play(unsigned int, int) = 0;
	virtual void togglePause() = 0;
	virtual void stop(int) = 0;
protected:
	virtual void load() = 0;

	///Path to the stored audio file
	std::string path;
};