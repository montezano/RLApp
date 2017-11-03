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

	initializeObservers(observer);

	ui.setupUi(this);


	//YourTableView.setModel(&mapmodel);

	QObject::connect(ui.add_exp_btn, SIGNAL(clicked()), this, SLOT(callAddREWindow()));
	QObject::connect(ui.add_grammar_btn, SIGNAL(clicked()), this, SLOT(callAddRGWindow()));
}

void RLApp::initializeObservers(Observer * observer)
{
	_add_re_window->addObserver(observer);
	_add_rg_window->addObserver(observer);

	_add_re_window->addObserver(this);
	_add_rg_window->addObserver(this);
}

void RLApp::callAddREWindow()
{
	_add_re_window->show();
	QList<QString> list = QList<QString>();
	list.append("value 11");
	list.append("value 12");
	list.append("value 13");
	list.append("value 14");

	QList<QString> list2 = QList<QString>();
	list2.append("value 21");
	list2.append("value 22");
	list2.append("value 23");
	list2.append("value 24");

	QList<QString> list3 = QList<QString>();
	list3.append("value 31");
	list3.append("value 32");
	list3.append("value 33");
	list3.append("value 34");
	map.insert("S", list );
	map.insert("A", list2);
	map.insert("B", list3);

	mapmodel.setMap(&map);



	
	ui.table_fa->setModel(&mapmodel);
	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->hide();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();

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
	case UPDATE_REGULAR_EXPRESSION:
		ui.line_re->insert(*(QString*)entity);
		//ui.table_rg->row()

		break;
	case UPDATE_REGULAR_GRAMMAR:

		break;

	case UPDATE_FINITE_AUTOMATA:

		break;
	}
}
