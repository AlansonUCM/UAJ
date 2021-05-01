#include "SamplingTracker.h"

#include "TrackerEvent.h"

SamplingTracker::SamplingTracker()
{
}

bool SamplingTracker::accept(const TrackerEvent& e)
{
	return e.getType() == "Sampling";
}
