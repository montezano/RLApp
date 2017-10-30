#include "controller/MainController.h"

MainController::MainController()
{
}

MainController::~MainController()
{
}

int MainController::run(int argc, char *argv[])
{
	w = new RLApp();
	w->show();

	return 0;
}

RLApp* MainController::w = NULL;