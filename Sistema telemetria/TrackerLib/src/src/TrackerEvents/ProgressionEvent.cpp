#include "ProgressionEvent.h"

#define stringify(name) # name

ProgressionEvent::ProgressionEvent() : TrackerEvent(), state()
{
}

void ProgressionEvent::setState(int state)
{
	this->state = (State)state;
}

int ProgressionEvent::getState() const
{
	return (int)state;
}

std::string ProgressionEvent::toJSON() const
{
	json j;

	generalPropertiesToJSON(j);
	j["state"] = stringify(state);
	eventPropertiesToJSON(j);

	return j.dump(4);
}

std::string ProgressionEvent::toCSV() const
{
	std::string atributes;
	std::string values;

	generalPropertiesToCSV(atributes, values);

	atributes += "state,";
	values += ',' + stringify(state);

	eventPropertiesToCSV(atributes, values);

	return atributes + "\n" + values;
}