#ifndef __MAINCONTROLLER_H__
#define __MAINCONTROLLER_H__

#include "view/RLApp.h"
#include "util/Observer.h"

class MainController: public Observer, public Subject
{
public:
	MainController();
	~MainController();

	int run();

	virtual void onNotify(void *data, Events event);

private:
	RLApp* _main_window;


	QString msg;
};


#endif // !__MAINCONTROLLER_H__
