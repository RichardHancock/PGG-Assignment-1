#pragma once

#include "Audio.h"

/**
@class Music
@brief Encapsulates music

Only one Music class can play at a time, there is no check for this so the outcome is unhandled.
*/
class Music : public Audio
{
public:
	Music(std::string);
	~Music();

	/**
	@brief Play the stored music
	
	@param unsigned int - milliseconds of fade-in
	@param int - How many times will this music play (-1 for infinite)
	*/
	void play(unsigned int, int);

	/**
	@brief Pause/Resume the current music track
	*/
	void togglePause();

	/**
	@brief Stop the stored music

	@param unsigned int - milliseconds of fade-out
	*/
	void stop(int);
private:
	/**
	@brief Loads a music file and store it internally
	*/
	void load();

	///Music data
	Mix_Music* music;
};