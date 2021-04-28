#pragma once
#include "TrackerEvent.h"

class SamplingEvent : public TrackerEvent
{
public:
	SamplingEvent();

	std::string toJSON();
	std::string toCSV();
};