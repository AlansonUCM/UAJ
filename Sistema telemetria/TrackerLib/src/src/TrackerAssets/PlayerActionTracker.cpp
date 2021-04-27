#include "PlayerActionTracker.h"

#include "TrackerEvent.h"

PlayerActionTracker::PlayerActionTracker()
{
}

bool PlayerActionTracker::accept(const TrackerEvent& e)
{
	return false;
}
