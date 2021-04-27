#include "Tracker.h"

int main()
{
	Tracker* tracker = Tracker::getInstance();
	tracker->init();

	// atributos: posX, posY, bossPhase, levelIndex
	//tracker->trackEvent("PlayerDie", "23.45", "56.23", "2", "1");
}