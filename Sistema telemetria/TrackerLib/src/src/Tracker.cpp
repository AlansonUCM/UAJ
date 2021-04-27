#include "Tracker.h"

#include "IPersistence.h"
#include "ITrackerAsset.h"
#include "TrackerEvent.h"

#include "FilePersistence.h"
#include "ServerPersistence.h"

#include "json.hpp"

#include <fstream>
#include <string>

using json = nlohmann::json;

Tracker* Tracker::instance = nullptr;

Tracker::Tracker()
{

}

Tracker::~Tracker()
{
	delete instance;
}

void Tracker::init()
{
	// Lee el fichero .config y configura el tracker
	std::ifstream file(".config");
	json j;
	file >> j;

	std::string persistenceType = "File";//j["persistence"];
	std::string serializerType = "JSON";//j["serializer"];
	//std::string serializerType = j["deactivatedEvents"];

	// Inicializa sistema de persistencia y serializacion
	// TODO: mejor una factoria
	if (persistenceType == "File")
		persistenceObject = new FilePersistence();
	else if (persistenceType == "Server")
		persistenceObject = new ServerPersistence();

	persistenceObject->init(serializerType);

	// Crea hilo
	exit = false;
	thread = new std::thread(&IPersistence::update, persistenceObject);

}

void Tracker::end()
{
	exit = true;
	thread->join();

	delete thread;
}

void Tracker::trackEvent(const TrackerEvent& e)
{
	// Funcion que se llama desde el juego
	int i = 0;
	while (i < activeTrackers.size() && !activeTrackers[i]->accept(e))
		i++;

	if (i < activeTrackers.size())
		persistenceObject->send(e);
}

Tracker* Tracker::getInstance()
{
	if (instance == nullptr)
		instance = new Tracker();

	return instance;
}