#pragma once
#include "TrackerEvent.h"

class InstantaneousEvent : public TrackerEvent
{
public:
	InstantaneousEvent();

	std::string toJSON();
	std::string toCSV();
};