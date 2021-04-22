#pragma once

#include "ITrackerAsset.h"

class ProgressionTracker : public ITrackerAsset
{
private:
	//enum EventType

public:
	ProgressionTracker();

	bool accept(TrackerEvent e);

};