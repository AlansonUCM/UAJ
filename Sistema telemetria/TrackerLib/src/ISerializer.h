#pragma once

#include <string>
#include "TrackerEvent.h"

class ISerializer
{
private:


public:
	virtual std::string serialize(TrackerEvent e) = 0;

};