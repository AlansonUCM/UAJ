#pragma once

#include "ITrackerAsset.h"

class ProgressionTracker : public ITrackerAsset
{
private:

public:
	ProgressionTracker();

	bool accept(const TrackerEvent& e);
};