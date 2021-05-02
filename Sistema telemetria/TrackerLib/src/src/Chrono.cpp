#include "Chrono.h"

double Chrono::tickInicial;
double Chrono::lastTime;
std::chrono::system_clock::time_point Chrono::startTime;

// Inicializa el cronometo
void Chrono::start()
{
	tickInicial = 0.0;
	lastTime = 0.0;
	startTime = std::chrono::system_clock::now();

	tickInicial = getTicks();
}

// Devuelve el tiempo transcurrido desde la inicializacion (llamada a start() )
double Chrono::stop()
{
	return getTicks() - tickInicial;
}

// Devuelve el tiempo transcurrido desde el start y actualiza el lastTime
double Chrono::getDeltaTime()
{
	double prevLastTime = lastTime;
	lastTime = getTicks();
	return lastTime - prevLastTime;
}

double Chrono::getTicks()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	return std::chrono::duration<double, std::milli>(now - startTime).count();
}


