#include "TimeBasedEvent.h"

TimeBasedEvent::TimeBasedEvent() : TrackerEvent(), state()
{
}

void TimeBasedEvent::setState(bool state)
{
	this->state = state;
}

bool TimeBasedEvent::getState() const
{
	return state;
}

std::string TimeBasedEvent::toJSON() const
{
	json j;

	generalPropertiesToJSON(j);
	j["state"] = state;
	eventPropertiesToJSON(j);

	return j.dump(4);
}

std::string TimeBasedEvent::toCSV() const
{
	std::string atributes;
	std::string values;

	generalPropertiesToCSV(atributes, values);

	atributes += "state,";
	values += ',' + state;

	eventPropertiesToCSV(atributes, values);

	return atributes + "\n" + values;
}