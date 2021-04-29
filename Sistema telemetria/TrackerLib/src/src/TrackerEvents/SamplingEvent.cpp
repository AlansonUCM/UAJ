#include "SamplingEvent.h"

SamplingEvent::SamplingEvent() : TrackerEvent()
{
}

std::string SamplingEvent::toJSON() const
{
	return TrackerEvent::toJSON();
}

std::string SamplingEvent::toCSV() const
{
	return TrackerEvent::toCSV();
}