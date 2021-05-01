#pragma once
#include "ITrackerAsset.h"
class TimeBasedTracker : public ITrackerAsset
{
private:

public:
	TimeBasedTracker();

	bool accept(const TrackerEvent& e);
};

