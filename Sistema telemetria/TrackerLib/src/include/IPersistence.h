#pragma once

#include <queue>
#include <atomic>

#include "ConcurrentQueue.h"
#include "TrackerEvent.h"

class ISerializer;

class IPersistence
{
private:

protected:
	enum class PersistenceMode { Checkpoint, Timed };
	PersistenceMode mode = PersistenceMode::Checkpoint;

	std::atomic_bool exit;
	std::atomic_bool flushing;

	ISerializer* serializer = nullptr;
	ConcurrentQueue<TrackerEvent> eventQueue;

	std::queue<TrackerEvent> eventsToFlush;

public:
	virtual void init(const std::string& type) = 0;
	virtual void end() = 0;

	virtual void update() = 0;

	virtual void send(TrackerEvent e) = 0;
	virtual void flush() = 0;

};