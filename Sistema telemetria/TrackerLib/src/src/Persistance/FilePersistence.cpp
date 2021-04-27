#include "FilePersistence.h"

#include "JSONSerializer.h"
#include "CSVSerializer.h"

FilePersistence::FilePersistence()
{

}

FilePersistence::~FilePersistence()
{
}

void FilePersistence::init(const std::string& type)
{
	// TODO: mejor una factoria
	if (type == "JSON")
		serializer = new JSONSerializer();
	else if (type == "CSV")
		serializer = new CSVSerializer();
}

void FilePersistence::end()
{
	exit = true;
}

void FilePersistence::update()
{
	while (!exit)
	{
		if (eventQueue.empty())
			continue;

		TrackerEvent e = eventQueue.pop();
		eventsToFlush.push(e);

		// Si el modo de volcado es por checkpoint
		// y es un evento checkpoint, se hace flush
		if (mode == PersistenceMode::Checkpoint &&
			e.getType() == EventType::Instantaneous &&
			e.getName() == EventName::EndLevel &&
			e.getName() == EventName::EndSession &&
			e.getName() == EventName::PlayerDie)
			flush();
	}
}

void FilePersistence::send(TrackerEvent e)
{
	eventQueue.push(e);
}

void FilePersistence::flush()
{
	// Vacia la cola de eventos listos para ser volcados
	while (!eventsToFlush.empty())
	{
		serializer->serialize(eventsToFlush.front());
		eventsToFlush.pop();
	}
}