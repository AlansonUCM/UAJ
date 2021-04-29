#include "TrackerEvent.h"
#include "json.hpp"

using json = nlohmann::json;

TrackerEvent::TrackerEvent() : name(""), gameID(""), sessionID(""), userID(""), checkpoint(false), eventProperties({})
{
}

void TrackerEvent::setName(std::string name)
{
	this->name = name;
}

void TrackerEvent::setTimestamp(double time)
{
	timestamp = time;
}

void TrackerEvent::setGameID(std::string game)
{
	gameID = game;
}

void TrackerEvent::setSessionID(std::string session)
{
	sessionID = session;
}

void TrackerEvent::setUserID(std::string user)
{
	userID = user;
}

void TrackerEvent::setCheckpoint(bool checkpoint)
{
	this->checkpoint = checkpoint;
}

std::string TrackerEvent::getName() const
{
	return name;
}

float TrackerEvent::getTimestamp() const
{
	return timestamp;
}

std::string TrackerEvent::getGameID() const
{
	return gameID;
}

std::string TrackerEvent::getSessionID() const
{
	return sessionID;
}

std::string TrackerEvent::getUserID() const
{
	return userID;
}

bool TrackerEvent::getCheckpoint() const
{
	return checkpoint;
}

std::vector<std::string> TrackerEvent::getKeys() const
{
	return keys;
}

std::map<std::string, double> TrackerEvent::getEventProperties() const
{
	return eventProperties;
}

std::string TrackerEvent::toJSON() const
{
	json j;
	j["name"] = name;
	j["timestamp"] = timestamp;
	j["gameID"] = gameID;
	j["sessionID"] = sessionID;
	j["userID"] = userID;
	j["checkpoint"] = checkpoint;
	
	int i = 0;
	while (i < keys.size())
	{
		j[keys[i]] = eventProperties.at(keys[i]);
		i++;
	}

	return j.dump(-1,'\n');
}

std::string TrackerEvent::toCSV() const
{
	std::string csv = "type," + name + "\n";
	csv += "timestamp," + std::to_string(timestamp) + "\n";
	csv += "gameID," + gameID + "\n";
	csv += "sessionID," + sessionID + "\n";
	csv += "userID," + userID + "\n";
	csv += "checkpoint," + std::to_string(checkpoint) + "\n";

	int i = 0;
	while (i < keys.size())
	{
		csv += keys[i] + " " + std::to_string(eventProperties.at(keys[i])) + "\n";
		i++;
	}

	return csv;
}