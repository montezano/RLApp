#include "util/Subject.h"

void Subject::addObserver(Observer * observer)
{
	_observers.push_back(observer);
}

void Subject::removeObserver(Observer * observer)
{
	//std::remove_if(_observers.begin(), _observers.end(), observer);
}

void Subject::notify(void *data, Events event)
{
	for (auto observer : _observers)
	{
		observer->onNotify(data, event);
	}
}