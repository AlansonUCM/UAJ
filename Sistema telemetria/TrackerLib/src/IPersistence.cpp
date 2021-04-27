#include "IPersistence.h"

void IPersistence::setSerializer(ISerializer* serial)
{
	serializer = serial;
}
