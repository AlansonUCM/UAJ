#pragma once
#include "TrackerEvent.h"
#include "TrackerExports.h"
class TRACKER_CORE_API InstantaneousEvent : public TrackerEvent
{
public:
	InstantaneousEvent();

	virtual std::string toJSON() const;
	virtual std::string toCSV() const;
};