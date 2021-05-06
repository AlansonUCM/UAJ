#include "Utils.h"

std::string Utils::getTime()
{
	time_t rawtime;
	struct tm timeInfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeInfo, &rawtime);

	strftime(buffer, 80, "%d-%m-%Y %H-%M-%S", &timeInfo);
	
	return std::string(buffer);
};