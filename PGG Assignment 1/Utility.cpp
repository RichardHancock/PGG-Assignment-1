#include "Utility.h"

void Utility::randomInit()
{
	srand((unsigned int) time(NULL));
}

int Utility::randomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

float Utility::randomFloat(float min, float max)
{
	// From http://stackoverflow.com/a/5289624
	// Could have used C++11 for random floats, but I think this is adequate.
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

void Utility::log(LogType type, std::string message)
{
	//Get current time
	time_t currentTime = time(NULL);
	tm timeStruct;
	localtime_s(&timeStruct, &currentTime);
	char textTime[9];

	//strftime(textTime, 11, "%T", &timeStruct); Apparently only Microsoft don't support the %T.
	strftime(textTime,9, "%H:%M:%S", &timeStruct);

	std::cout << textTime;

	switch (type)
	{
	case I:
		std::cout << " Info: ";
		break;
	case W:
		std::cout << " Warning: ";
		break;
	case E:
		std::cout << " Error: ";
		break;
	default:
		std::cout << " ???: ";
		break;
	}

	std::cout << message.c_str() << std::endl;
}

Vec2 Utility::getRectCenter(SDL_Rect rect)
{
	Vec2 center;
	center.x = (float)(rect.x + (rect.w / 2));
	center.y = (float)(rect.y + (rect.h / 2));
	return center;
}