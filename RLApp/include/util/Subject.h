#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>
#include <algorithm>

#include "Observer.h"
#include "Event.h"

class Subject
{
public:
	void addObserver(Observer *observer);
	void removeObserver(Observer *observer);
protected:
	void notify(void *entity, Events event);

private:
	std::vector<Observer*> _observers;

};
#endif // !__SUBJECT_H__
