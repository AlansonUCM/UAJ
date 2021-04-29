#include "FilePersistence.h"

#include <ctime>

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
	exit = false;

	// TODO: mejor una factoria
	// Crea el serializer
	if (type == "JSON")
		serializer = new JSONSerializer();
	else if (type == "CSV")
		serializer = new CSVSerializer();

	// Crea el archivo de trazas para esta sesion
	// con nombre: fecha y hora
	time_t rawtime;
	struct tm timeInfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeInfo, &rawtime);

	strftime(buffer, 80, "%d-%m-%Y %H-%M-%S", &timeInfo);
	fileName = "logs/" + std::string(buffer) + ".log";

	logFile.open(fileName, std::ios_base::app); // append instead of overwrite
	logFile << "log creado\n";
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

		printf("%s\n", e.getName().c_str());

		// Si el modo de volcado es por checkpoint
		// y es un evento checkpoint, se hace flush
		if (mode == PersistenceMode::Checkpoint && e.getCheckpoint())
			flush();
	}
}

void FilePersistence::send(TrackerEvent e)
{
	eventQueue.push(e);
}

void FilePersistence::flush()
{
	flushing = true;

	printf("start flush\n");

	// Vuelca la cola de eventos listos para ser volcados
	// en el archivo de trazas
	std::string text = "";

	while (!eventsToFlush.empty())
	{
		text += serializer->serialize(eventsToFlush.front()) + "\n";

		eventsToFlush.pop();
	}

	printf("%s\n", text.c_str());

	logFile.open(fileName, std::ios_base::app); // append instead of overwrite
	logFile << text; //logFile.write(text.c_str(), text.length());

	flushing = false;
}