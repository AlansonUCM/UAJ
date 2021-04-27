#pragma once

#include <queue>

#include "ISerializer.h"
#include "TrackerEvent.h"
#include "ConcurrentQueue.h"

class IPersistence
{
private:

protected:
	enum class PersistenceMode { Checkpoint, Timed };
	PersistenceMode mode;

	ISerializer* serializer = nullptr;
	ConcurrentQueue<TrackerEvent> eventQueue;

	std::queue<TrackerEvent> eventsToFlush;

public:
	virtual void init(const std::string& type) = 0;

	virtual void update() = 0;

	virtual void send(TrackerEvent e) = 0;
	virtual void flush() = 0;

};