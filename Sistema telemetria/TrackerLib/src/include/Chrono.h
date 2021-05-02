#pragma once

#include <chrono>

class Chrono
{
private:
	static double tickInicial;
	static double lastTime;
	static std::chrono::system_clock::time_point startTime;

	static double getTicks();

public:
	static void start();
	static double stop();
	static double getDeltaTime();
};