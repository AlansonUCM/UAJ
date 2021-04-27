#include "IPersistence.h"

void IPersistence::setSerializer(const ISerializer* serial)
{
	serializer = serial;
}
