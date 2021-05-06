#include "Utils.h"

std::string Utils::getTime()
{
	time_t rawtime;
	struct tm timeInfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeInfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H-%M-%S", &timeInfo);

	return buffer;
};