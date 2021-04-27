#include "TrackerEvent.h"
#include "json.hpp"

using json = nlohmann::json;

TrackerEvent::TrackerEvent() : type(EventType::Instantaneous), sessionID(0), timestamp(0)
{
}

void TrackerEvent::setType(EventType type)
{
	this->type = type;
}

void TrackerEvent::setName(EventName name)
{
}

EventType TrackerEvent::getType() const
{
	return type;
}

EventName TrackerEvent::getName() const
{
	return EventName();
}

void TrackerEvent::setSessionID(int sessionID)
{
	this->sessionID = sessionID;
}

int TrackerEvent::getSessionID() const
{
	return sessionID;
}

void TrackerEvent::setTimestamp(float timestamp)
{
	this->timestamp = timestamp;
}

float TrackerEvent::getTimestamp() const
{
	return timestamp;
}

std::string TrackerEvent::toJSON() const
{
	json j;
	j["type"] = type;
	j["sessionID"] = sessionID;
	j["timestamp"] = timestamp;
	return j.dump();
}

std::string TrackerEvent::toCSV() const
{
	std::string typeString = "type," + std::to_string((int)type) + "\n";
	std::string sessionIDString = "sessionID," + std::to_string(sessionID) + "\n";
	std::string timestampString = "timestamp," + std::to_string(timestamp) + "\n";
	return typeString + sessionIDString + timestampString;
}