#include "RLApp.h"

RLApp::RLApp(QWidget *parent)
	: QMainWindow(parent)
{
	_add_re_window = new AddReWindow();
	_add_rg_window = new AddRgWindow();

	ui.setupUi(this);

	QObject::connect(ui.add_exp_btn, SIGNAL(clicked()), this, SLOT(callAddREWindow()));
	QObject::connect(ui.add_grammar_btn, SIGNAL(clicked()), this, SLOT(callAddRGWindow()));
}

RLApp::RLApp(Observer* observer, QWidget *parent)
	: QMainWindow(parent)
{
	_add_re_window = new AddReWindow();
	_add_rg_window = new AddRgWindow();

	_add_re_window->addObserver(observer);
	_add_rg_window->addObserver(observer);

	ui.setupUi(this);

	QObject::connect(ui.add_exp_btn, SIGNAL(clicked()), this, SLOT(callAddREWindow()));
	QObject::connect(ui.add_grammar_btn, SIGNAL(clicked()), this, SLOT(callAddRGWindow()));
}

void RLApp::callAddREWindow()
{
	_add_re_window->show();
}

void RLApp::callAddRGWindow()
{
	_add_rg_window->show();
}

void RLApp::callAddFAWindow()
{

}

void RLApp::onNotify(void * entity, Events event)
{
	switch (event)
	{
	}
}
