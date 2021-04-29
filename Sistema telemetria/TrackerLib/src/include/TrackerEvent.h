#pragma once
#include <string>
#include <vector>
#include <map>

class TrackerEvent
{
private:
	std::string name;
	std::string timestamp;
	std::string gameID, sessionID, userID;
	bool checkpoint;

	std::vector<std::string> keys;
	std::map<std::string, double> eventProperties;

public:
	TrackerEvent();

	void setName(const std::string& name);
	void setTimestamp(const std::string& time);
	void setGameID(const std::string& game);
	void setSessionID(const std::string& session);
	void setUserID(const std::string& user);
	void setCheckpoint(bool checkpoint);

	std::string getName() const;
	std::string getTimestamp() const;
	std::string getGameID() const;
	std::string getSessionID() const;
	std::string getUserID() const;
	bool getCheckpoint() const;

	std::vector<std::string> getKeys() const;
	std::map<std::string, double> getEventProperties() const;

	std::string toJSON() const;
	std::string toCSV() const;
};