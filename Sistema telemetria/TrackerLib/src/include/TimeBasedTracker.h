#pragma once
#include "ITrackerAsset.h"
#include "TrackerExports.h"
class TRACKER_CORE_API TimeBasedTracker : public ITrackerAsset
{
private:

public:
	TimeBasedTracker();

	bool accept(const TrackerEvent& e);
};

