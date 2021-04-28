#include "SamplingEvent.h"

SamplingEvent::SamplingEvent()
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