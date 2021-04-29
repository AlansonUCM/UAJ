#include "InstantaneousEvent.h"

InstantaneousEvent::InstantaneousEvent() : TrackerEvent()
{
}

std::string InstantaneousEvent::toJSON() const
{
	return TrackerEvent::toJSON();
}

std::string InstantaneousEvent::toCSV() const
{
	return TrackerEvent::toCSV();
}