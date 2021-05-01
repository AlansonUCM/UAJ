#include "InstantaneousTracker.h"

#include "TrackerEvent.h"

InstantaneousTracker::InstantaneousTracker()
{
}

bool InstantaneousTracker::accept(const TrackerEvent& e)
{
	return e.getType() == "Instantaneous";
}