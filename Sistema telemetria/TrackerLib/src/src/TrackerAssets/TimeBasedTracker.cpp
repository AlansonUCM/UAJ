#include "TimeBasedTracker.h"

#include "TrackerEvent.h"

TimeBasedTracker::TimeBasedTracker()
{
}

bool TimeBasedTracker::accept(const TrackerEvent& e)
{
    return e.getType() == "TimeBased";
}
