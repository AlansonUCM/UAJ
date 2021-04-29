
#include "CSVSerializer.h"

#include "TrackerEvent.h"

CSVSerializer::CSVSerializer()
{

}

std::string CSVSerializer::serialize(const TrackerEvent* e)
{
	return e->toCSV();
}