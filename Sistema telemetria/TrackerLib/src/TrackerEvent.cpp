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

EventType TrackerEvent::getType()
{
	return type;
}

void TrackerEvent::setSessionID(int sessionID)
{
	this->sessionID = sessionID;
}

int TrackerEvent::getSessionID()
{
	return sessionID;
}

void TrackerEvent::setTimestamp(float timestamp)
{
	this->timestamp = timestamp;
}

float TrackerEvent::getTimestamp()
{
	return timestamp;
}

std::string TrackerEvent::toJSON()
{
	json j;
	j["type"] = type;
	j["sessionID"] = sessionID;
	j["timestamp"] = timestamp;
	return j.dump();
}

std::string TrackerEvent::toCSV()
{
	std::string typeString = "type," + std::to_string((int)type) + "\n";
	std::string sessionIDString = "sessionID," + std::to_string(sessionID) + "\n";
	std::string timestampString = "timestamp," + std::to_string(timestamp) + "\n";
	return typeString + sessionIDString + timestampString;
}