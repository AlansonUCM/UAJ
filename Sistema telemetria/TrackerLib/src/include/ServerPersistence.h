#pragma once

#include "IPersistence.h"

#include "httplib.h"

class ServerPersistence : public IPersistence
{
private:
	httplib::Client* client = nullptr;

public:
	ServerPersistence();
	~ServerPersistence();

	virtual void init(const std::string& type);
	virtual void end();

	virtual void update();

	virtual void send(TrackerEvent* e);
	virtual void flush();

};