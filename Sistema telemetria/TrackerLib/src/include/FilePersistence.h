#pragma once

#include "IPersistence.h"

class FilePersistence : public IPersistence
{

public:
	FilePersistence();
	~FilePersistence();

	virtual void init(const std::string& type);
	virtual void end();

	virtual void update();

	virtual void send(TrackerEvent e);
	virtual void flush();

};