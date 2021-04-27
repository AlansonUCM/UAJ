#pragma once

#include "ITrackerAsset.h"

class BossActionTracker : public ITrackerAsset
{
private:

public:
	BossActionTracker();

	bool accept(const TrackerEvent& e);
};

