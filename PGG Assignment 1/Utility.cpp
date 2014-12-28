#include "Utility.h"

void Utility::randomInit()
{
	srand(time(NULL));
}

int Utility::randomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void Utility::log(LogType type, char* message)
{
	//Get current time
	time_t currentTime = time(NULL);
	tm timeStruct;
	localtime_s(&timeStruct, &currentTime);
	char textTime[11];

	//strftime(textTime, 11, "%T", &timeStruct); Apparntly only Microsoft don't support the %T.
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

	std::cout << message << std::endl;
}