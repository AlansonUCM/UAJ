#pragma once

#include <string>
#include "TrackerEvent.h"

class ISerializer
{
private:


public:
	virtual std::string serialize(const TrackerEvent& e) = 0;

};