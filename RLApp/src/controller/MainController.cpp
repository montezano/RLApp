#include "controller/MainController.h"

MainController::MainController()
{
}

MainController::~MainController()
{
}

int MainController::run()
{
	_main_window = new MainWindow();
	_main_window->show();

	return 0;
}

MainWindow* MainController::_main_window = NULL;