#include "InstantaneousEvent.h"

InstantaneousEvent::InstantaneousEvent() : TrackerEvent()
{
}

std::string InstantaneousEvent::toJSON()
{
	return TrackerEvent::toJSON();
}

std::string InstantaneousEvent::toCSV()
{
	return TrackerEvent::toCSV();
}