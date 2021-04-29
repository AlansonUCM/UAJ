#include "SamplingEvent.h"

SamplingEvent::SamplingEvent() : TrackerEvent()
{
}

std::string SamplingEvent::toJSON()
{
	return TrackerEvent::toJSON();
}

std::string SamplingEvent::toCSV()
{
	return TrackerEvent::toCSV();
}