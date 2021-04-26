#pragma once

#include <string>

enum class EventType { Instantaneous, TimeBased, Sampling };

class TrackerEvent
{
private:
	EventType type;
	int sessionID;
	float timestamp;

public:
	TrackerEvent();

	void setType(EventType type);
	EventType getType();

	void setSessionID(int sessionID);
	int getSessionID();

	void setTimestamp(float timestamp);
	float getTimestamp();

	std::string toJSON();
	std::string toCSV();
};