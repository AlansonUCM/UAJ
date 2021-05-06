#pragma once
#include "TrackerEvent.h"
#include "TrackerExports.h"
enum class State { Started, Progressed, Finished };

class  TRACKER_CORE_API ProgressionEvent : public TrackerEvent
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