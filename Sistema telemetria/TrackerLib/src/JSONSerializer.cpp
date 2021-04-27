
#include "JSONSerializer.h"

JSONSerializer::JSONSerializer()
{

}

std::string JSONSerializer::serialize(TrackerEvent e)
{
	return e.toJSON();
}