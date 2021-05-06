#pragma once

#include <string>
#include "ISerializer.h"
#include "TrackerExports.h"
class TRACKER_CORE_API CSVSerializer : public ISerializer
{
private:


public:
	CSVSerializer();

	virtual std::string serialize(const TrackerEvent* e);

};