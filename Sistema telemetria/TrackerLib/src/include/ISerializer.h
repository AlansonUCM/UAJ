#pragma once

#include <string>

class TrackerEvent;

class ISerializer
{
private:


public:
	virtual std::string serialize(const TrackerEvent& e) = 0;

};