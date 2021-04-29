#include "Tracker.h"
#include "TrackerEvent.h"
#include <windows.h>

int main()
{
	Tracker* tracker = Tracker::getInstance();
	tracker->init();

	// Prueba
	tracker->trackInstantaneousEvent("BossHit", {});
	tracker->trackInstantaneousEvent("AmmoCollected", {});
	tracker->trackInstantaneousEvent("EndLevel", {}, true);

	Sleep(2000);

	tracker->trackInstantaneousEvent("PlayerShoot", {});
	tracker->trackProgressEvent("normalolololo", {}, false, 1);
	tracker->trackTimeBasedEvent("normalelelele", {}, false, false);

	Sleep(2000);

	tracker->trackInstantaneousEvent("PlayerShoot", {});
	tracker->trackInstantaneousEvent("PlayerDie", {}, true);

	while (true);
}