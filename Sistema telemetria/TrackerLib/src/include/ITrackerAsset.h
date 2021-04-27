#pragma once

#include "TrackerExports.h"

class TrackerEvent;

class TRACKER_CORE_API ITrackerAsset
{
private:


public:
	virtual bool accept(const TrackerEvent& e) = 0;

};