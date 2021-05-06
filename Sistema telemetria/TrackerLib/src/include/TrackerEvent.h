#pragma once
#include <string>
#include <vector>
#include <map>
#include "json.hpp"
#include "TrackerExports.h"

using json = nlohmann::json;

class TRACKER_CORE_API TrackerEvent
{
private:
	std::string gameID, sessionID, userID;
	std::string timestamp;
	std::string type;
	std::string name;
	bool checkpoint;

	std::map<std::string, std::string> eventProperties;

protected:
	void generalPropertiesToJSON(json& j) const;
	void eventPropertiesToJSON(json& j) const;

	void generalPropertiesToCSV(std::string& atributes, std::string& values) const;
	void eventPropertiesToCSV(std::string& atributes, std::string& values) const;

public:
	TrackerEvent();

	void setGameID(const std::string& game);
	void setSessionID(const std::string& session);
	void setUserID(const std::string& user);
	void setTimestamp(const std::string& time);
	void setType(const std::string& type);
	void setName(const std::string& name);
	void setCheckpoint(bool checkpoint);

	void setEventProperties(std::map<std::string, std::string> properties);

	std::string getGameID() const;
	std::string getSessionID() const;
	std::string getUserID() const;
	std::string getTimestamp() const;
	std::string getType() const;
	std::string getName() const;
	bool getCheckpoint() const;

	std::map<std::string, std::string>* getEventProperties();

	virtual std::string toJSON() const;
	virtual std::string toCSV() const;
};