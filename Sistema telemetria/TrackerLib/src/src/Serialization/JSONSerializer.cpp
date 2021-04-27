
#include "JSONSerializer.h"

#include "TrackerEvent.h"

JSONSerializer::JSONSerializer()
{

}

std::string JSONSerializer::serialize(const TrackerEvent& e)
{
	return e.toJSON();
}