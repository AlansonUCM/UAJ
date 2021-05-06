#include "ServerPersistence.h"

#include "JSONSerializer.h"
#include "CSVSerializer.h"

#include "Chrono.h"

ServerPersistence::ServerPersistence()
{

}

ServerPersistence::~ServerPersistence()
{

}

void ServerPersistence::init(const std::string& type, const std::string& mode, const double& timeRate)
{
	this->mode = mode;
	this->timeRate = timeRate;

	serializerFactory.registerType<JSONSerializer>("JSONSerializer");
	serializerFactory.registerType<CSVSerializer>("CSVSerializer");

	exit = false;

	// Crea el serializer
	serializer = serializerFactory.create(type);

	// Crea el cliente (se conecta al server)
	client = new httplib::Client("localhost", 8080);

	// Obtener trazas actuales del server y printearlas
	/*httplib::Result res = client->Get("/tracker");
	printf("get: %s", res->body.c_str());*/
}

void ServerPersistence::end()
{
	
	exit = true;
}

void ServerPersistence::update()
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
	flush();
	Chrono::stop();
	delete serializer;
	delete client;
}

void ServerPersistence::send(TrackerEvent* e)
{
	eventQueue.push(e);
}

void ServerPersistence::flush()
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
	if(text!="")
		httplib::Result res = client->Post("/tracker", text, "text/plain");

	flushing = false;
}