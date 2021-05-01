#include "Tracker.h"

#include <json.hpp>
#include <fstream>
#include <string>

#include "IPersistence.h"
#include "ITrackerAsset.h"
#include "TrackerEvent.h"

#include "FilePersistence.h"
#include "ServerPersistence.h"

#include "TimeBasedEvent.h"
#include "InstantaneousEvent.h"
#include "ProgressionEvent.h"
#include "SamplingEvent.h"

#include "InstantaneousTracker.h"
#include "SamplingTracker.h"
#include "TimeBasedTracker.h"
#include "ProgressionTracker.h"

#include "machineID.h"
#include "md5Hash.h"
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
	initFactories();

	// Lee el fichero .config y configura el tracker
	std::ifstream file("config.json");
	json j = json::parse(file);

	std::string persistenceType = *j.find("persistence");
	std::string serializerType = *j.find("serializer");
	json activeTrackersJson = *j.find("activeTrackers");

	for (json::iterator it = activeTrackersJson.begin(); it != activeTrackersJson.end(); ++it) {
		ITrackerAsset* tracker = trackersFactory.create(*it);
		if (tracker != nullptr)
			activeTrackers.push_back(tracker);
	}

	// Inicializa sistema de persistencia y serializacion
	persistenceObject = persistanceFactory.create(persistenceType);
	if (persistenceObject != nullptr)
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
	int i = 0;
	while (i < activeTrackers.size() && !activeTrackers[i]->accept(*e))
		i++;

	if (i < activeTrackers.size())
		persistenceObject->send(e);
}

void Tracker::initFactories()
{
	trackersFactory.registerType<InstantaneousTracker>("InstantaneousTracker");
	trackersFactory.registerType<TimeBasedTracker>("TimeBasedTracker");
	trackersFactory.registerType<SamplingTracker>("SamplingTracker");
	trackersFactory.registerType<ProgressionTracker>("ProgressionTracker");

	persistanceFactory.registerType<FilePersistence>("FilePersistence");
	persistanceFactory.registerType<ServerPersistence>("ServerPersistence");
}

Tracker* Tracker::getInstance()
{
	if (instance == nullptr)
		instance = new Tracker();

	return instance;
}