#pragma once

#include <string>
#include "ISerializer.h"

class CSVSerializer : public ISerializer
{
private:


public:
	CSVSerializer();

	virtual std::string serialize(const TrackerEvent& e);

};