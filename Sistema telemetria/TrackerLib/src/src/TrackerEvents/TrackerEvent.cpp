#include "TrackerEvent.h"

void TrackerEvent::generalPropertiesToJSON(json& j) const
{
	j["gameID"] = gameID;
	j["sessionID"] = sessionID;
	j["userID"] = userID;
	j["timestamp"] = timestamp;
	j["type"] = type;
	j["name"] = name;
	j["checkpoint"] = checkpoint;
}

void TrackerEvent::eventPropertiesToJSON(json& j) const
{
	auto it = eventProperties.begin();
	while (it != eventProperties.end())
	{
		j[(*it).first] = (*it).second;
		it++;
	}
}

void TrackerEvent::generalPropertiesToCSV(std::string& atributes, std::string& values) const
{
	atributes = "gameID,sessionID,userID,timestamp,type,name,checkpoint";
	values = gameID + "," + sessionID + "," + userID + "," + timestamp + "," + type + "," + name + "," + std::to_string(checkpoint);
}

void TrackerEvent::eventPropertiesToCSV(std::string& atributes, std::string& values) const
{
	auto it = eventProperties.begin();
	while (it != eventProperties.end())
	{
		atributes += "," + (*it).first;
		values += "," + (*it).second;
		it++;
	}
}

TrackerEvent::TrackerEvent() : gameID(""), sessionID(""), userID(""), timestamp(""), type(""), name(""), checkpoint(false), eventProperties({})
{
}

void TrackerEvent::setGameID(const std::string& game)
{
	gameID = game;
}

void TrackerEvent::setSessionID(const std::string& session)
{
	sessionID = session;
}

void TrackerEvent::setUserID(const std::string& user)
{
	userID = user;
}

void TrackerEvent::setTimestamp(const std::string& time)
{
	timestamp = time;
}

void TrackerEvent::setType(const std::string& type)
{
	this->type = type;
}

void TrackerEvent::setName(const std::string& name)
{
	this->name = name;
}

void TrackerEvent::setCheckpoint(bool checkpoint)
{
	this->checkpoint = checkpoint;
}

void TrackerEvent::setEventProperties(std::map<std::string, std::string> properties)
{
	this->eventProperties = properties;
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

std::string TrackerEvent::getTimestamp() const
{
	return timestamp;
}

std::string TrackerEvent::getType() const
{
	return type;
}

std::string TrackerEvent::getName() const
{
	return name;
}

bool TrackerEvent::getCheckpoint() const
{
	return checkpoint;
}

std::map<std::string, std::string>* TrackerEvent::getEventProperties()
{
	return &eventProperties;
}

std::string TrackerEvent::toJSON() const
{
	json j;

	generalPropertiesToJSON(j);
	eventPropertiesToJSON(j);

	return j.dump(4);
}

std::string TrackerEvent::toCSV() const
{
	std::string atributes;
	std::string values;

	generalPropertiesToCSV(atributes, values);
	eventPropertiesToCSV(atributes, values);

	return atributes + "\n" + values;
}