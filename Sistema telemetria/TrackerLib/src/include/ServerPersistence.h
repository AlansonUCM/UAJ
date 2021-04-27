#pragma once

#include "IPersistence.h"

class ServerPersistence : public IPersistence
{
private:


public:
	ServerPersistence();
	~ServerPersistence();

	virtual void init(const std::string& type);
	virtual void end();

	virtual void update();

	virtual void send(TrackerEvent e);
	virtual void flush();

};