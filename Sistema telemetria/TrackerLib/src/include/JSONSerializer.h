#pragma once

#include <string>
#include "ISerializer.h"
#include "TrackerExports.h"
class TRACKER_CORE_API JSONSerializer : public ISerializer
{
private:


public:
	JSONSerializer();

	virtual std::string serialize(const TrackerEvent* e);

};