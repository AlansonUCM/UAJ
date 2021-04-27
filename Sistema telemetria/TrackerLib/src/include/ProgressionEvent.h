#pragma once

#include "TrackerEvent.h"

class ProgressionEvent : public TrackerEvent
{
private:
	//enum EventType

public:
	ProgressionEvent();

	std::string toJSON();
	std::string toCSV();

};