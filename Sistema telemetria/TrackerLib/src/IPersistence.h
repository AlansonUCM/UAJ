#pragma once

#include "TrackerEvent.h"

class IPersistence
{
private:


public:
	virtual void send(TrackerEvent e) = 0;
	virtual void flush() = 0;

};