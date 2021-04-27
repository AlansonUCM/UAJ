
#include "JSONSerializer.h"

JSONSerializer::JSONSerializer()
{

}

std::string JSONSerializer::serialize(const TrackerEvent& e)
{
	return e.toJSON();
}