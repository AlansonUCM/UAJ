#pragma once

#include "IPersistence.h"

class ServerPersistence
{
private:


public:
	ServerPersistence();

	virtual void send(TrackerEvent e);
	virtual void flush();

};