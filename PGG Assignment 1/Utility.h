#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef UTILITY_H
#define UTILITY_H

namespace Utility
{
	/**
	@brief Initialize the Random Number functions

	Call this before any random functions, else random will be the same 
	sequence of numbers for each program execution.
	*/
	void randomInit();

	/**
	@brief Generate a random number between min and max
	
	@param int - Minimum Number for the range
	@param int - Maximum Number for the range
	@return int - Random int between min and max
	*/
	int randomInt(int min, int max);
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

#endif 