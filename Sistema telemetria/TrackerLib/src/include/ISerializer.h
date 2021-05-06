#pragma once

#include <string>
#include "TrackerExports.h"
class TrackerEvent;

class TRACKER_CORE_API ISerializer
{
private:


public:
	virtual std::string serialize(const TrackerEvent* e) = 0;

};