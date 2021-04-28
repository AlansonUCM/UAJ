#pragma once
#include "TrackerEvent.h"

class TimeBaseEvent : public TrackerEvent
{
public:
	TimeBaseEvent();

	std::string toJSON();
	std::string toCSV();
};