#include "Utility.h"

void Utility::randomInit()
{
	srand(time(NULL));
}

int Utility::randomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}