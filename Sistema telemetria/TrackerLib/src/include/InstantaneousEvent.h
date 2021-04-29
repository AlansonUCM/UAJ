#pragma once
#include "TrackerEvent.h"

class InstantaneousEvent : public TrackerEvent
{
public:
	InstantaneousEvent();

	virtual std::string toJSON() const;
	virtual std::string toCSV() const;
};