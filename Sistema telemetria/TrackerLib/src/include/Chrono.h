#pragma once

#include <chrono>
#include "TrackerExports.h"
class TRACKER_CORE_API Chrono
{
private:
	static double tickInicial;
	static double lastTime;
	static std::chrono::system_clock::time_point startTime;

public:
	static void start();
	static double stop();
	static double getDeltaTime();
	static double getTicks();
};