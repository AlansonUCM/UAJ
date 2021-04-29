#include "Tracker.h"

#include "TrackerEvent.h"

int main()
{
	Tracker* tracker = Tracker::getInstance();
	tracker->init();

	// atributos: posX, posY, bossPhase, levelIndex
	//tracker->trackEvent("PlayerDie", "23.45", "56.23", "2", "1");

	// prueba
	tracker->trackInstantaneousEvent("BossHit", {});
	tracker->trackInstantaneousEvent("AmmoCollected", {});
	tracker->trackInstantaneousEvent("EndLevel", {}, true);

	while (true);
}