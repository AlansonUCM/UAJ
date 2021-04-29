#pragma once

#include <vector>
#include <thread>

#include "TrackerExports.h"

class IPersistence;
class ITrackerAsset;
class TrackerEvent;

class /*TRACKER_CORE_API*/ Tracker
{
private:
	static Tracker* instance;
	IPersistence* persistenceObject;
	std::vector<ITrackerAsset*> activeTrackers;

	std::thread* thread;

public:
	Tracker();
	virtual ~Tracker();

	static Tracker* getInstance();

	void init();
	void end();
	void trackEvent(const TrackerEvent& e);

};