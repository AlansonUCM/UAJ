#pragma once
#include "TrackerEvent.h"

enum class State { Started, Progressed, Finished };

class ProgressionEvent : public TrackerEvent
{
private:
	State state;

public:
	ProgressionEvent();

	void setState(int state);

	int getState() const;

	virtual std::string toJSON() const;
	virtual std::string toCSV() const;
};