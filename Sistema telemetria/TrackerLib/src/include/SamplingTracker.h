#pragma once
#include "ITrackerAsset.h"
class SamplingTracker : public ITrackerAsset
{
private:

public:
	SamplingTracker();

	bool accept(const TrackerEvent& e);
};

