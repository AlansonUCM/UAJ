#include "TimeBaseEvent.h"

TimeBaseEvent::TimeBaseEvent()
{
}

std::string TimeBaseEvent::toJSON()
{
	return TrackerEvent::toJSON();
}

std::string TimeBaseEvent::toCSV()
{
	return TrackerEvent::toCSV();
}