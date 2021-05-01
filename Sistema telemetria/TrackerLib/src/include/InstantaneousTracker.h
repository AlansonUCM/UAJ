#pragma once

#include "ITrackerAsset.h"

class InstantaneousTracker : public ITrackerAsset
{
private:

public:
	InstantaneousTracker();

	bool accept(const TrackerEvent& e);
};

