#pragma once

#include "TrackerEvent.h"

class ITrackerAsset
{
private:


public:
	virtual bool accept(TrackerEvent e) = 0;

};