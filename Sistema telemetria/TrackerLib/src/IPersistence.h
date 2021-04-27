#pragma once
#include "ISerializer.h"
#include "TrackerEvent.h"

class IPersistence
{
private:
	const ISerializer* serializer=nullptr;

public:

	void setSerializer(const ISerializer* serial);
	virtual void send(TrackerEvent e) = 0;
	virtual void flush() = 0;

};