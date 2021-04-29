#include "TimeBasedEvent.h"

TimeBasedEvent::TimeBasedEvent() : TrackerEvent()
{
}

std::string TimeBasedEvent::toJSON()
{
	return TrackerEvent::toJSON();
}

std::string TimeBasedEvent::toCSV()
{
	return TrackerEvent::toCSV();
}