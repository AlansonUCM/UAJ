#include "Tracker.h"

#include "IPersistence.h"
#include "ITrackerAsset.h"
#include "TrackerEvent.h"

#include "FilePersistence.h"
#include "ServerPersistence.h"

#include "TimeBasedEvent.h"
#include "InstantaneousEvent.h"
#include "ProgressionEvent.h"
#include "SamplingEvent.h"

#include "machineID.h"
#include "md5Hash.h"

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
	std::ifstream file("config.json");
	json j = json::parse(file);

	std::string persistenceType = /*"File"*/ *j.find("persistence");
	std::string serializerType = /*"JSON"*/*j.find("serializer");
	//std::string serializerType = j["deactivatedEvents"];

	// Inicializa sistema de persistencia y serializacion
	// TODO: mejor una factoria
	if (persistenceType == "File")
		persistenceObject = new FilePersistence();
	else if (persistenceType == "Server")
		persistenceObject = new ServerPersistence();

	persistenceObject->init(serializerType);

	//Obtiene el ID de la sesion
	double timestamp = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
	sessionId = md5(machineHash() + std::to_string(timestamp));

	// Crea hilo
	thread = new std::thread(&IPersistence::update, persistenceObject);
}

void Tracker::end()
{
	thread->join();

	delete thread;
}

void Tracker::trackInstantaneousEvent(std::string name, std::map<std::string, double> eventProperties, bool checkpoint)
{
	TrackerEvent event = InstantaneousEvent();
	double timestamp = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
	event.setName(name);
	event.setTimestamp(timestamp);
	event.setSessionID(sessionId);
	event.setCheckpoint(checkpoint);

	trackEvent(event);
}

void Tracker::trackProgressEvent(std::string name, std::map<std::string, double> eventProperties, bool checkpoint, int state)
{
	TrackerEvent event = ProgressionEvent();
	double timestamp = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
	event.setName(name);
	event.setTimestamp(timestamp);
	event.setSessionID(sessionId);
	event.setCheckpoint(checkpoint);

	//Progress of the event

	trackEvent(event);
}

void Tracker::trackSamplingEvent(std::string name, std::map<std::string, double> eventProperties, bool checkpoint)
{
	TrackerEvent event =  SamplingEvent();
	double timestamp = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
	event.setName(name);
	event.setTimestamp(timestamp);
	event.setSessionID(sessionId);
	event.setCheckpoint(checkpoint);

	//Add Sampling (Añadir el evento recurrentemente a la cola)????

	trackEvent(event);
}

void Tracker::trackTimeBasedEvent(std::string name, std::map<std::string, double> eventProperties, bool checkpoint, bool end)
{
	TrackerEvent event = TimeBasedEvent();
	double timestamp = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
	event.setName(name);
	event.setTimestamp(timestamp);
	event.setSessionID(sessionId);
	event.setCheckpoint(checkpoint);

	//Begining or end of the event

	trackEvent(event);
}

void Tracker::trackEvent(const TrackerEvent& e)
{
	// Funcion que se llama desde el juego
	/*int i = 0;
	while (i < activeTrackers.size() && !activeTrackers[i]->accept(e))
		i++;

	if (i < activeTrackers.size())*/
	persistenceObject->send(e);
}

Tracker* Tracker::getInstance()
{
	if (instance == nullptr)
		instance = new Tracker();

	return instance;
}