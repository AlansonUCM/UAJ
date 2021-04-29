#include "Tracker.h"

#include "TrackerEvent.h"

#include <windows.h>



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

	Sleep(2000);

	tracker->trackInstantaneousEvent("PlayerShoot", {});
	Sleep(2000);
	tracker->trackInstantaneousEvent("PlayerShoot", {});
	tracker->trackInstantaneousEvent("PlayerDie", {}, true);
	
	/*TrackerEvent e = TrackerEvent();
	e.setName("BossHit");
	TrackerEvent e1 = TrackerEvent();
	e1.setName("AmmoCollected");
	TrackerEvent e2 = TrackerEvent();
	e2.setName("EndLevel");
	e2.setCheckpoint(true);

	tracker->trackEvent(e);
	tracker->trackEvent(e1);
	tracker->trackEvent(e2);*/

	while (true);
}