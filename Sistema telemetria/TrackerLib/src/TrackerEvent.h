#pragma once

#include <string>

enum class EventType { Instantaneous, TimeBased, Sampling };
enum class EventName 
{ 
	InitSession,
	EndSession,
	StartLevel,
	EndLevel,
	PlayerDie,
	AmmoCollected,
	PlayerShoot,
	PlayerHit,
	BossAttack,
	BossHit
};

class TrackerEvent
{
private:
	EventType type;
	EventName name;
	int sessionID;
	float timestamp;

public:
	TrackerEvent();

	void setType(EventType type);
	void setName(EventName name);
	void setSessionID(int sessionID);
	void setTimestamp(float timestamp);

	EventType getType() const;
	EventName getName() const;
	int getSessionID() const;
	float getTimestamp() const;

	std::string toJSON() const;
	std::string toCSV() const;
};