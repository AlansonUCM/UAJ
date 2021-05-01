#include "FilePersistence.h"

#include "JSONSerializer.h"
#include "CSVSerializer.h"
#include "json.hpp"

#include "Utils.h"

using jsonf = nlohmann::json;

FilePersistence::FilePersistence()
{

}

FilePersistence::~FilePersistence()
{
}

void FilePersistence::init(const std::string& type)
{
	serializerFactory.registerType<JSONSerializer>("JSONSerializer");
	serializerFactory.registerType<CSVSerializer>("CSVSerializer");

	exit = false;

	// Crea el serializer
	serializer = serializerFactory.create(type);

	// Crea el archivo de trazas para esta sesion
	// con nombre: fecha y hora
	fileName = "logs/" + std::string(Utils::getTime()) + ".log";

	logFile.open(fileName);
	logFile.close();
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

		TrackerEvent* e = eventQueue.pop();
		eventsToFlush.push(e);

		printf("%s\n", e->getName().c_str());

		// Si el modo de volcado es por checkpoint
		// y es un evento checkpoint, se hace flush
		if (mode == PersistenceMode::Checkpoint && e->getCheckpoint())
			flush();
	}
}

void FilePersistence::send(TrackerEvent* e)
{
	eventQueue.push(e);
}

void FilePersistence::flush()
{
	flushing = true;

	printf("flush\n");

	// Vuelca la cola de eventos listos para ser volcados
	// en el archivo de trazas
	std::string text = "";

	while (!eventsToFlush.empty())
	{
		TrackerEvent* e = eventsToFlush.front();
		text += serializer->serialize(e) + "\n";

		printf("flushed: %s\n", e->getName().c_str());

		eventsToFlush.pop();
		delete e;
	}

	//printf("%s\n", text.c_str());

	// append instead of overwrite
	logFile.open(fileName, std::ios_base::app);
	logFile << text;

	logFile.close();

	flushing = false;
}