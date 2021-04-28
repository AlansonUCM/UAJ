#pragma once
#include "TrackerEvent.h"

class ProgressionEvent : public TrackerEvent
{
public:
	ProgressionEvent();

	std::string toJSON();
	std::string toCSV();
};