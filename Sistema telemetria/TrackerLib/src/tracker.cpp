#include "Tracker.h"

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

}

void Tracker::end()
{

}

void Tracker::trackEvent()
{

}

Tracker* Tracker::getInstance()
{
    if (instance == nullptr)
        instance = new Tracker();

    return instance;
}