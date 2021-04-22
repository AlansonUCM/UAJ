#pragma once

#include <string>

class TrackerEvent
{
private:
	//enum EventType

public:
	TrackerEvent();

	std::string toJSON();
	std::string toCSV();

};