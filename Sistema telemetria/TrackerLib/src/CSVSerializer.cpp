
#include "CSVSerializer.h"

CSVSerializer::CSVSerializer()
{

}

std::string CSVSerializer::serialize(const TrackerEvent& e)
{
	return e.toCSV();
}