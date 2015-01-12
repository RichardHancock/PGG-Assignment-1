#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <SDL.h>

#include "Vec2.h"

#pragma once

/**
@brief An assortment of useful functions (random numbers, logging) that don't fit elsewhere.
*/
namespace Utility
{
	/**
	@brief Initialize the Random Number functions

	Call this before any random functions, else random will be the same
	sequence of numbers for each program execution.
	*/
	void randomInit();

	/**
	@brief Generate a random integer number between min and max

	@param int - Minimum Number for the range
	@param int - Maximum Number for the range
	@return int - Random int between min and max
	*/
	int randomInt(int min, int max);

	/**
	@brief Generate a random float number between min and max

	@todo This function is possibly unstable, it just started working with no real changes.

	@param float - Minimum Number for the range
	@param float - Maximum Number for the range
	@return float - Random float between min and max
	*/
	float randomFloat(float min, float max);

	/**
	@brief A type of log message
	*/
	enum LogType
	{
		E, //< Error
		W, //< Warning
		I  //< Info
	};

	/**
	@brief Log a message to the console

	Made this one function instead of multiple to reduce clutter. Could have used SDL_Log instead.
	@param LogType - Type of message E: Error, W: Warning, I: Info
	@param char* - The message to log
	*/
	void log(LogType, std::string);

	/**
	@brief Returns the center position of a rectangle
	@param SDL_Rect - Rectangle struct
	@return Vec2 - Center position of the rectangle
	*/
	Vec2 getRectCenter(SDL_Rect rect);

}

/**
@brief Defines a RGB colour
*/
struct Colour
{
	uint8_t r; //< Red Channel
	uint8_t g; //< Green Channel
	uint8_t b; //< Blue Channel

	Colour(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};

