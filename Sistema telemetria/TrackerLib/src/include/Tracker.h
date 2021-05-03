#pragma once

#include <vector>
#include <thread>
#include <map>

#include "TrackerExports.h"
#include "Factory.h"

class IPersistence;
class ITrackerAsset;
class TrackerEvent;

class /*TRACKER_CORE_API*/ Tracker
{
private:
	static Tracker* instance;
	IPersistence* persistenceObject;
	std::vector<ITrackerAsset*> activeTrackers;

	std::string sessionId;

	std::map<std::string, float> samplingEvents;
	float samplingTimer = 2000;

	Factory<ITrackerAsset> trackersFactory;
	Factory<IPersistence> persistanceFactory;

	std::thread* thread;
	void trackEvent(TrackerEvent* e);
	void initFactories();

public:
	Tracker();
	virtual ~Tracker();

	static Tracker* getInstance();

	void init();
	void end();

	void trackInstantaneousEvent(std::string name, std::map<std::string, std::string> eventProperties, bool checkpoint = false);
	void trackProgressEvent(std::string name, std::map<std::string, std::string> eventProperties, bool checkpoint = false, int state = 0);
	void trackSamplingEvent(std::string name, std::map<std::string, std::string> eventProperties, bool checkpoint = false);
	void trackTimeBasedEvent(std::string name, std::map<std::string, std::string> eventProperties, bool checkpoint = false, bool end = false);

};