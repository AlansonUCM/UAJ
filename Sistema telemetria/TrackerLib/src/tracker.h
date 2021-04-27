#pragma once

#include <vector>
#include <atomic>
#include <thread>

#include "IPersistence.h"
#include "ITrackerAsset.h"

class Tracker
{
private:
	static Tracker* instance;
	IPersistence* persistenceObject;
	std::vector<ITrackerAsset*> activeTrackers;

	std::atomic_bool exit;
	std::thread* thread;

public:
	Tracker();
	virtual ~Tracker();

	static Tracker* getInstance();

	void init();
	void end();
	void trackEvent(const TrackerEvent& e);

};