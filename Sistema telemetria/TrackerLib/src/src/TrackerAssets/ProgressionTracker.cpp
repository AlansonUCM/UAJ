#include "ProgressionTracker.h"

#include "TrackerEvent.h"

ProgressionTracker::ProgressionTracker()
{
}

bool ProgressionTracker::accept(const TrackerEvent& e)
{
	return e.getType() == "Progression";
}