#pragma once
#include "ISerializer.h"
#include "TrackerEvent.h"

class IPersistence
{
private:
	ISerializer* serializer=nullptr;

public:

	void setSerializer(ISerializer* serial);
	virtual void send(TrackerEvent e) = 0;
	virtual void flush() = 0;

};