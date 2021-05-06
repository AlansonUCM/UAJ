#pragma once
#include "ITrackerAsset.h"
#include "TrackerExports.h"
class TRACKER_CORE_API SamplingTracker : public ITrackerAsset
{
private:

public:
	SamplingTracker();

	bool accept(const TrackerEvent& e);
};

