#include "TrackerEvent.h"
#include "json.hpp"

using json = nlohmann::json;

TrackerEvent::TrackerEvent() : name(""), gameID(0), sessionID(0), userID(0), checkpoint(false), eventProperties(std::map<std::string, double>())
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

void TrackerEvent::setGameID(int game)
{
	gameID = game;
}

void TrackerEvent::setSessionID(int session)
{
	sessionID = session;
}

void TrackerEvent::setUserID(int user)
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

int TrackerEvent::getGameID() const
{
	return gameID;
}

int TrackerEvent::getSessionID() const
{
	return sessionID;
}

int TrackerEvent::getUserID() const
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

	return j.dump();
}

std::string TrackerEvent::toCSV() const
{
	std::string csv = "type," + name + "\n";
	csv += "timestamp," + std::to_string(timestamp) + "\n";
	csv += "gameID," + std::to_string(gameID) + "\n";
	csv += "sessionID," + std::to_string(sessionID) + "\n";
	csv += "userID," + std::to_string(userID) + "\n";
	csv += "checkpoint," + std::to_string(checkpoint) + "\n";

	int i = 0;
	while (i < keys.size())
	{
		csv += keys[i] + " " + std::to_string(eventProperties.at(keys[i])) + "\n";
		i++;
	}

	return csv;
}