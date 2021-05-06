#include "Tracker.h"
#include "TrackerEvent.h"
#include <windows.h>

int main()
{
	Tracker* tracker = Tracker::getInstance();
	//tracker->init();

	// Prueba
	tracker->trackInstantaneousEvent("AmmoCollected", {});
	tracker->trackInstantaneousEvent("BossHit", {});
	tracker->trackInstantaneousEvent("EndLevel", {}, true);

	Sleep(2000);

	tracker->trackSamplingEvent("PlayerHit", {});
	tracker->trackSamplingEvent("PlayerShoot", {});
	tracker->trackProgressEvent("normalolololo", {}, false, 1);
	tracker->trackTimeBasedEvent("normalelelele", {}, false, false);

	Sleep(3000);

	tracker->trackSamplingEvent("PlayerShoot", {});
	tracker->trackInstantaneousEvent("PlayerDie", {}, true);

	while (true);
}