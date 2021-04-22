#pragma once

#include "IPersistence.h"

class FilePersistence
{

public:
	FilePersistence();

	virtual void send(TrackerEvent e);
	virtual void flush();

};