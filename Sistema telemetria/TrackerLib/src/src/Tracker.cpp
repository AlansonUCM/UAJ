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

#include "Utils.h"

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

void Tracker::trackInstantaneousEvent(std::string name, std::map<std::string, std::string> eventProperties, bool checkpoint)
{
	InstantaneousEvent* event = new InstantaneousEvent();
	//double timestamp = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
	event->setType("Instantaneous");
	event->setName(name);
	event->setTimestamp(Utils::getTime()); //timestamp);
	event->setSessionID(sessionId);
	event->setCheckpoint(checkpoint);
	event->setEventProperties(eventProperties);

	trackEvent(event);
}

void Tracker::trackProgressEvent(std::string name, std::map<std::string, std::string> eventProperties, bool checkpoint, int state)
{
	ProgressionEvent* event = new ProgressionEvent();
	//double timestamp = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
	event->setType("Progression");
	event->setName(name);
	event->setTimestamp(Utils::getTime());
	event->setSessionID(sessionId);
	event->setCheckpoint(checkpoint);
	event->setEventProperties(eventProperties);

	//Progress of the event
	event->setState(state);

	trackEvent(event);
}

void Tracker::trackSamplingEvent(std::string name, std::map<std::string, std::string> eventProperties, bool checkpoint)
{
	SamplingEvent* event = new SamplingEvent();
	//double timestamp = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
	event->setType("Sampling");
	event->setName(name);
	event->setTimestamp(Utils::getTime());
	event->setSessionID(sessionId);
	event->setCheckpoint(checkpoint);
	event->setEventProperties(eventProperties);

	//Add Sampling (Añadir el evento recurrentemente a la cola)????

	trackEvent(event);
}

void Tracker::trackTimeBasedEvent(std::string name, std::map<std::string, std::string> eventProperties, bool checkpoint, bool end)
{
	TimeBasedEvent* event = new TimeBasedEvent();
	//double timestamp = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
	event->setType("TimeBased");
	event->setName(name);
	event->setTimestamp(Utils::getTime());
	event->setSessionID(sessionId);
	event->setCheckpoint(checkpoint);
	event->setEventProperties(eventProperties);

	//Begining or end of the event
	event->setState(end);

	trackEvent(event);
}

void Tracker::trackEvent(TrackerEvent* e)
{
	persistenceObject->send(e);
}

Tracker* Tracker::getInstance()
{
	if (instance == nullptr)
		instance = new Tracker();

	return instance;
}