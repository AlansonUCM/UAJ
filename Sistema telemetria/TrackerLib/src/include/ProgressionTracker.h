#pragma once

#include "ITrackerAsset.h"
#include "TrackerExports.h"
class TRACKER_CORE_API ProgressionTracker : public ITrackerAsset
{
private:

public:
	ProgressionTracker();

	bool accept(const TrackerEvent& e);
};