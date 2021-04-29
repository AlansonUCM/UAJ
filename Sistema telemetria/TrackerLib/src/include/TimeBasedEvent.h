#pragma once
#include "TrackerEvent.h"

class TimeBasedEvent : public TrackerEvent
{
private:
	bool state;

public:
	TimeBasedEvent();

	void setState(bool state);

	bool getState() const;

	virtual std::string toJSON() const;
	virtual std::string toCSV() const;
};