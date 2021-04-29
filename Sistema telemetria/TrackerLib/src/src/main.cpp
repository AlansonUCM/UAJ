#include "Tracker.h"

#include "TrackerEvent.h"

int main()
{
	Tracker* tracker = Tracker::getInstance();
	tracker->init();

	// atributos: posX, posY, bossPhase, levelIndex
	//tracker->trackEvent("PlayerDie", "23.45", "56.23", "2", "1");

	// prueba
	TrackerEvent e = TrackerEvent();
	e.setName("BossHit");
	TrackerEvent e1 = TrackerEvent();
	e1.setName("AmmoCollected");
	TrackerEvent e2 = TrackerEvent();
	e2.setName("EndLevel");

	tracker->trackEvent(e);
	tracker->trackEvent(e1);
	tracker->trackEvent(e2);

	while (true);
}