#include "ProgressionEvent.h"

ProgressionEvent::ProgressionEvent() : TrackerEvent()
{
}

std::string ProgressionEvent::toJSON()
{
	return TrackerEvent::toJSON();
}

std::string ProgressionEvent::toCSV()
{
	return TrackerEvent::toCSV();
}