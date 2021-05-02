#include "FilePersistence.h"

#include "JSONSerializer.h"
#include "CSVSerializer.h"
#include "json.hpp"

#include "Utils.h"

#include "Chrono.h"

using jsonf = nlohmann::json;

FilePersistence::FilePersistence()
{

}

FilePersistence::~FilePersistence()
{
}

void FilePersistence::init(const std::string& type, const std::string& mode, const double& timeRate)
{
	this->mode = mode;
	this->timeRate = timeRate;

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
	Chrono::start();

	while (!exit)
	{
		// Timer
		if (mode == "Timed")
		{
			if (time < timeRate)
				time += Chrono::getDeltaTime() / 1000.0;
			else
			{
				flush();
				time = 0.0f;
			}
		}


		if (eventQueue.empty())
			continue;

		TrackerEvent* e = eventQueue.pop();
		eventsToFlush.push(e);

		printf("%s\n", e->getName().c_str());

		// Si el modo de volcado es por checkpoint
		// y es un evento checkpoint, se hace flush
		if (mode == "Checkpoint" && e->getCheckpoint())
			flush();
	}

	Chrono::stop();
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