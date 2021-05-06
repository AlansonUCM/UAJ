#include "Tracker.h"

#include <json.hpp>
#include <fstream>
#include<iostream>
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
#include "Chrono.h"

using json = nlohmann::json;

Tracker* Tracker::instance = nullptr;

std::string readJsonString(std::ifstream& json)
{
	char c;
	std::string result;
	json >> c;
	do
	{
		json >> c;
		while (c != '"' && c != '\n' && !json.eof())
		{
			result += c;
			json >> c;

		}
	} while (c != '"' && c != '\n' && !json.eof());
	json >> c;
	return result;
}

Tracker::Tracker()
{
}

Tracker::~Tracker()
{
	//	delete instance;
}

void Tracker::init()
{
	initFactories();

	// Lee el fichero .config y configura el tracker
	std::ifstream file;//("config.json");
	file.open("config.json");
	//bool ok = file.is_open();
	std::string help;

	std::string persistenceType;
	std::string persistenceMode;
	double timeRate;
	std::string serializerType;
	char itChar;

	if (file.is_open()) {

		std::getline(file, help);
		while (!file.eof()) {
			size_t index;
			help = readJsonString(file);


			if (help == "persistence")
			{
				persistenceType = readJsonString(file);

			}
			else if (help == "persistenceMode")
			{
				persistenceMode = readJsonString(file);
			}
			else if (help == "timeRate")
			{
				file >> timeRate;
				file >> help;

				samplingTimer = timeRate * 1000;
			}
			else if (help == "serializer")
			{
				serializerType = readJsonString(file);
			}
			else if (help == "activeTrackers")
			{
				file >> itChar;
				while (help != "" && !file.eof())
				{
					help = readJsonString(file);

					if (help != "")
					{
						ITrackerAsset* tracker = trackersFactory.create(help);
						if (tracker != nullptr)
							activeTrackers.push_back(tracker);
					}

				}
			}
		}
	}


	// Inicializa sistema de persistencia y serializacion
	persistenceObject = persistanceFactory.create(persistenceType);
	if (persistenceObject != nullptr)
		persistenceObject->init(serializerType, persistenceMode, timeRate);

	//Obtiene el ID de la sesion
	double timestamp = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
	sessionId = md5(machineHash() + std::to_string(timestamp));

	// Crea hilo
	thread = new std::thread(&IPersistence::update, persistenceObject);
}

void Tracker::init(std::string gameId, std::string userId)
{
	gameID = gameId;
	userID = userId;
	init();
}

void Tracker::end()
{

	persistenceObject->end();
	thread->join();
	delete persistenceObject;
	while (activeTrackers.size() != 0)
	{
		delete activeTrackers.back();
		activeTrackers.pop_back();
	}
	delete thread;
}

void Tracker::trackInstantaneousEvent(std::string name, std::map<std::string, std::string> eventProperties, bool checkpoint)
{
	InstantaneousEvent* event = new InstantaneousEvent();
	event->setGameID(gameID);
	event->setUserID(userID);
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
	event->setGameID(gameID);
	event->setUserID(userID);
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
	event->setGameID(gameID);
	event->setUserID(userID);
	event->setType("Sampling");
	event->setName(name);
	event->setTimestamp(Utils::getTime());
	event->setSessionID(sessionId);
	event->setCheckpoint(checkpoint);
	event->setEventProperties(eventProperties);


	auto it = samplingEvents.find(name);
	if (it == samplingEvents.end())
	{
		samplingEvents[name] = Chrono::getTicks();
		trackEvent(event);
	}
	else
	{
		float currentSamplingTime = Chrono::getTicks();
		if (currentSamplingTime - (*it).second > samplingTimer)
		{
			(*it).second = currentSamplingTime;
			trackEvent(event);
		}
	}
}

void Tracker::trackTimeBasedEvent(std::string name, std::map<std::string, std::string> eventProperties, bool checkpoint, bool end)
{
	TimeBasedEvent* event = new TimeBasedEvent();
	event->setGameID(gameID);
	event->setUserID(userID);
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

void Tracker::deleteInstance()
{
	delete instance;
}