#pragma once

#include "ITrackerAsset.h"
#include "TrackerExports.h"
class TRACKER_CORE_API InstantaneousTracker : public ITrackerAsset
{
private:

public:
	InstantaneousTracker();

	bool accept(const TrackerEvent& e);
};

