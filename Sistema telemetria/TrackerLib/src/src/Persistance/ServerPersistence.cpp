#include "ServerPersistence.h"

#include "JSONSerializer.h"
#include "CSVSerializer.h"

ServerPersistence::ServerPersistence()
{

}

ServerPersistence::~ServerPersistence()
{

}

void ServerPersistence::init(const std::string& type)
{
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

	httplib::Result res = client->Post("/tracker", text, "text/plain");

	flushing = false;
}