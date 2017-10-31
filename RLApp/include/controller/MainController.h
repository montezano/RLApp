#ifndef __MAINCONTROLLER_H__
#define __MAINCONTROLLER_H__

#include "view\MainWindow.h"


class MainController
{
public:
	MainController();
	~MainController();

	static int run();

private:
	static MainWindow* _main_window;

};


#endif // !__MAINCONTROLLER_H__
