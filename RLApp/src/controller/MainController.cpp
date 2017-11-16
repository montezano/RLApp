#include "controller/MainController.h"

MainController::MainController()
{
	FADataModel* fa = new FADataModel();
	
	_model_controller = new ModelController(_main_window, fa);
	_main_window = new RLApp(_model_controller, fa);

	initializeObservers();
}

MainController::~MainController()
{
}

void MainController::initializeObservers()
{
	addObserver(_main_window);

	_main_window->addObserver(this);
	_main_window->addObserver(_model_controller);

	_model_controller->addObserver(_main_window);
}

int MainController::run()
{
	_main_window->show();

	return 0;
}

void MainController::onNotify(void * data, Events event)
{
	switch (event)
	{
	//case ADD_REGULAR_GRAMMAR:
	//	//msg = "blah";
	//	//notify(&msg, Events::ANOTAAI)
	//	notify(data, event);
	//	break;
	//	
	//case ADD_REGULAR_EXPRESSION:
	//	notify(data, event);
	//	break;

	//case ADD_FINITE_AUTOMATA:
	//	break;
	}
}

//RLApp* MainController::_main_window = NULL;