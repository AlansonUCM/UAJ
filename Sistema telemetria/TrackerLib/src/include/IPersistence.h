#pragma once

#include <queue>
#include <atomic>

#include "ConcurrentQueue.h"
#include "TrackerEvent.h"
#include "Factory.h"
#include "TrackerExports.h"

class ISerializer;

class TRACKER_CORE_API IPersistence
{
private:

protected:
	std::string mode = "";

	double time = 0.0;
	double timeRate = 0.0;

	std::atomic_bool exit;
	std::atomic_bool flushing;

	ISerializer* serializer = nullptr;
	ConcurrentQueue<TrackerEvent*> eventQueue;
	Factory<ISerializer> serializerFactory;

	std::queue<TrackerEvent*> eventsToFlush;

public:
	virtual void init(const std::string& type, const std::string& mode, const double& timeRate) = 0;
	virtual void end() = 0;

	virtual void update() = 0;

	virtual void send(TrackerEvent* e) = 0;
	virtual void flush() = 0;

};