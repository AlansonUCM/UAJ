#pragma once
#include "TrackerEvent.h"

class TimeBasedEvent : public TrackerEvent
{
public:
	TimeBasedEvent();

	std::string toJSON();
	std::string toCSV();
};