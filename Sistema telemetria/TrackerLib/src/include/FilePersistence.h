#pragma once

#include <fstream>

#include "IPersistence.h"

class FilePersistence : public IPersistence
{
private:
	std::ofstream logFile;
	std::string fileName;

public:
	FilePersistence();
	~FilePersistence();

	virtual void init(const std::string& type);
	virtual void end();

	virtual void update();

	virtual void send(TrackerEvent* e);
	virtual void flush();

};