
#include "CSVSerializer.h"

CSVSerializer::CSVSerializer()
{

}

std::string CSVSerializer::serialize(TrackerEvent e)
{
	return e.toCSV();
}