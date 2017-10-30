#ifndef __MAINCONTROLLER_H__
#define __MAINCONTROLLER_H__

#include "RLApp.h"


class MainController
{
public:
	MainController();
	~MainController();

	static int run(int argc, char *argv[]);

private:
	static RLApp* w;
};


#endif // !__MAINCONTROLLER_H__
