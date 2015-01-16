#pragma once

#include "Audio.h"

/**
@class SFX
@brief Encapsulates a Sound Effect
*/
class SFX : public Audio
{
public:
	SFX(std::string);
	~SFX();

	/**
	@brief Play the stored Sound Effect

	@param unsigned int - milliseconds of fade-in
	@param int - How many times will this music play (-1 for infinite , 0 to just play once)
	*/
	void play(unsigned int, int);

	/**
	@brief Pause/Resume the Sound Effect
	*/
	void togglePause();

	/**
	@brief Stop the stored Sound Effect

	@param unsigned int - milliseconds of fade-out
	*/
	void stop(int);
private:
	/**
	@brief Loads a Sound Effect file and store it internally
	*/
	void load();

	///Currently assigned channel for the sound effect
	int channel;

	///Sound data
	Mix_Chunk* sound;
};