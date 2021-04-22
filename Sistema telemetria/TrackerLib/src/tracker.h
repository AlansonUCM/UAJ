#pragma once

#include <vector>

#include "IPersistence.h"
#include "ITrackerAsset.h"

class Tracker
{
private:
	static Tracker* instance;
	IPersistence* persistenceObject;
	std::vector<ITrackerAsset> activeTrackers;

public:
	Tracker();
	virtual ~Tracker();

	static Tracker* getInstance();

	void init();
	void end();
	void trackEvent();

};