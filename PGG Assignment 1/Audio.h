#pragma once

#include <SDL_mixer.h>
#include <string>

/**
@class Audio
@brief Abstract base class for any Audio
*/
class Audio
{
public:
	/**
	@brief Create an Audio object
	@param std::string - Path to the audio file
	*/
	Audio(std::string);

	/**
	@brief Play the stored Audio

	@param unsigned int - milliseconds of fade-in
	@param int - How many times will this audio play (-1 for infinite , 0 to just play once)
	*/
	virtual void play(unsigned int, int) = 0;

	/**
	@brief Pause/Resume the audio
	*/
	virtual void togglePause() = 0;

	/**
	@brief Stop the stored Audio
	@param int - milliseconds of fade-out
	*/
	virtual void stop(int) = 0;
protected:
	/**
	@brief Loads a audio file and stores it internally
	*/
	virtual void load() = 0;

	///Path to the stored audio file
	std::string path;
};