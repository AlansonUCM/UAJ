#include "BossActionTracker.h"

#include "TrackerEvent.h"

BossActionTracker::BossActionTracker()
{
}

bool BossActionTracker::accept(const TrackerEvent& e)
{
	return false;
}
