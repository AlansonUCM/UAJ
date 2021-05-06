#pragma once

#include "IPersistence.h"
#include "TrackerExports.h"
#include "httplib.h"

class TRACKER_CORE_API ServerPersistence : public IPersistence
{
private:
	httplib::Client* client = nullptr;

public:
	ServerPersistence();
	~ServerPersistence();

	virtual void init(const std::string& type, const std::string& mode, const double& timeRate);
	virtual void end();

	virtual void update();

	virtual void send(TrackerEvent* e);
	virtual void flush();

};