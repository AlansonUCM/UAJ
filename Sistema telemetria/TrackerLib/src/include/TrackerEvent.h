#pragma once
#include <string>
#include <vector>
#include <map>

class TrackerEvent
{
private:
	std::string name;
	double timestamp;
	std::string gameID, sessionID, userID;
	bool checkpoint;

	std::vector<std::string> keys;
	std::map<std::string, double> eventProperties;

public:
	TrackerEvent();

	void setName(std::string name);
	void setTimestamp(double time);
	void setGameID(std::string game);
	void setSessionID(std::string session);
	void setUserID(std::string user);
	void setCheckpoint(bool checkpoint);

	std::string getName() const;
	float getTimestamp() const;
	std::string getGameID() const;
	std::string getSessionID() const;
	std::string getUserID() const;
	bool getCheckpoint() const;

	std::vector<std::string> getKeys() const;
	std::map<std::string, double> getEventProperties() const;

	std::string toJSON() const;
	std::string toCSV() const;
};