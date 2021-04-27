#pragma once

#include "ITrackerAsset.h"

class PlayerActionTracker : public ITrackerAsset
{
private:

public:
	PlayerActionTracker();

	bool accept(const TrackerEvent& e);
};

