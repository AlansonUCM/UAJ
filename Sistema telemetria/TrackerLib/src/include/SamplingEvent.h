#pragma once
#include "TrackerEvent.h"
#include "TrackerExports.h"
class TRACKER_CORE_API SamplingEvent : public TrackerEvent
{
public:
	SamplingEvent();

	virtual std::string toJSON() const;
	virtual std::string toCSV() const;
};