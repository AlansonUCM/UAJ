#pragma once

#include <string>
#include "ISerializer.h"

class JSONSerializer : public ISerializer
{
private:


public:
	JSONSerializer();

	virtual std::string serialize(const TrackerEvent& e);

};