#pragma once
#include "TrackerEvent.h"

class SamplingEvent : public TrackerEvent
{
public:
	SamplingEvent();

	virtual std::string toJSON() const;
	virtual std::string toCSV() const;
};