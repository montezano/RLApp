#include "RLApp.h"

RLApp::RLApp(QWidget *parent)
	: QMainWindow(parent)
{
	_add_re_window = new AddReWindow();
	_add_rg_window = new AddRgWindow();


	ui.setupUi(this);
	configureCallbacks();
}

RLApp::RLApp(Observer* observer, FADataModel* fa_data, QWidget *parent)
	: QMainWindow(parent),
	fa_model(fa_data)
{
	_add_re_window = new AddReWindow();
	_add_rg_window = new AddRgWindow();
	_add_fa_terminals_w = new AddFATerminalWindow();

	initializeObservers(observer);

	ui.setupUi(this);

	configureCallbacks();



	ui.table_fa->setModel(fa_data);
	//YourTableView.setModel(&mapmodel);
}

void RLApp::initializeObservers(Observer * observer)
{
	_add_re_window->addObserver(observer);
	_add_rg_window->addObserver(observer);

	_add_re_window->addObserver(this);
	_add_rg_window->addObserver(this);
	_add_fa_terminals_w->addObserver(this);
}

void RLApp::configureCallbacks()
{
	QObject::connect(ui.btn_add_re, SIGNAL(clicked()), this, SLOT(updateRE()));
	QObject::connect(ui.btn_op_re_to_fa, SIGNAL(clicked()), this, SLOT(reToFa()));
	QObject::connect(ui.btn_op_union_re, SIGNAL(clicked()), this, SLOT(reUnion()));
	QObject::connect(ui.btn_op_int_re, SIGNAL(clicked()), this, SLOT(reIntersection()));
	QObject::connect(ui.btn_op_comp_re, SIGNAL(clicked()), this, SLOT(reComplement()));
	QObject::connect(ui.btn_op_equ_re, SIGNAL(clicked()), this, SLOT(reEquivalence()));


	QObject::connect(ui.btn_op_gr_to_fa, SIGNAL(clicked()), this, SLOT(rgToFa()));
	QObject::connect(ui.btn_op_union_rg, SIGNAL(clicked()), this, SLOT(rgUnion()));
	QObject::connect(ui.btn_op_int_rg, SIGNAL(clicked()), this, SLOT(rgIntersection()));
	QObject::connect(ui.btn_op_comp_rg, SIGNAL(clicked()), this, SLOT(rgComplement()));
	QObject::connect(ui.btn_op_equ_rg, SIGNAL(clicked()), this, SLOT(rgEquivalence()));

	QObject::connect(ui.btn_op_union_fa, SIGNAL(clicked()), this, SLOT(faUnion()));
	QObject::connect(ui.btn_op_int_fa, SIGNAL(clicked()), this, SLOT(faIntersection()));
	QObject::connect(ui.btn_op_comp_fa, SIGNAL(clicked()), this, SLOT(faComplement()));
	QObject::connect(ui.btn_op_equi_fa, SIGNAL(clicked()), this, SLOT(faEquivalence()));
	QObject::connect(ui.btn_op_det_fa, SIGNAL(clicked()), this, SLOT(faDeterminization()));
	QObject::connect(ui.btn_op_min_fa, SIGNAL(clicked()), this, SLOT(faMinimization()));

	QObject::connect(ui.btn_add_trans_name, SIGNAL(clicked()), this, SLOT(faInsertTransitionName()));
	QObject::connect(ui.btn_add_trans, SIGNAL(clicked()), this, SLOT(faInsertTransition()));

	QObject::connect(ui.btn_rem_trans, SIGNAL(clicked()), this, SLOT(faRemoveTransition()));
	QObject::connect(ui.btn_rem_trans_name, SIGNAL(clicked()), this, SLOT(faRemoveTransitionName()));


	QObject::connect(ui.table_fa, SIGNAL(selectColumn()), this, SLOT(callAddRGWindow()));

	




}

//void RLApp::callAddREWindow()
//{
//	_add_re_window->show();
//	QList<QString> list = QList<QString>();
//	list.append("value 11");
//	list.append("value 12");
//	list.append("value 13");
//	list.append("value 14");
//
//	QList<QString> list2 = QList<QString>();
//	list2.append("value 21");
//	list2.append("value 22");
//	list2.append("value 23");
//	list2.append("value 24");
//
//	QList<QString> list3 = QList<QString>();
//	list3.append("value 31");
//	list3.append("value 32");
//	list3.append("value 33");
//	list3.append("value 34");
//	map.insert("S", list );
//	map.insert("A", list2);
//	map.insert("B", list3);
//
//	mapmodel.setMap(&map);
//
//
//
//	
//	ui.table_fa->setModel(&mapmodel);
//	ui.table_fa->show();
//	ui.table_fa->verticalHeader()->hide();
//	ui.table_fa->horizontalHeader()->hide();
//	ui.table_fa->resizeColumnsToContents();
//	ui.table_fa->resizeRowsToContents();
//
//}

void RLApp::callAddRGWindow()
{
	_add_rg_window->show();
}

void RLApp::callAddFAWindow()
{
	_add_rg_window->show();
}

void RLApp::onNotify(void * entity, Events event)
{
	switch (event)
	{
	case FA_ADD_TERMINAL:
		fa_model->insertColumn(fa_model->getTerminals().size());
		//fa_model->setData(*(QString*)entity);
		break;
	}
}

void RLApp::reToFa()
{
	notify((void*)ui.line_re, RE_TO_FA);
}

void RLApp::reUnion()
{
	notify((void*)ui.line_re, RE_UNION);
}

void RLApp::reIntersection()
{
	notify((void*)ui.line_re, RE_INTERSECTION);
}

void RLApp::reComplement()
{
	notify((void*)ui.line_re, RE_COMPLEMENT);
}

void RLApp::reEquivalence()
{
	notify((void*)ui.line_re, RE_EQUIVALENCE);
}

void RLApp::rgToFa()
{
	//notify((void*)ui.line_re, RG_EQUIVALENCE);

}

void RLApp::rgUnion()
{
}

void RLApp::rgIntersection()
{
}

void RLApp::rgComplement()
{
}

void RLApp::rgEquivalence()
{
}

void RLApp::faUnion()
{
	notify(NULL, FA_UNION);
}

void RLApp::faIntersection()
{
	notify(NULL, FA_INTERSECTION);
}

void RLApp::faComplement()
{
	notify(NULL, FA_COMPLEMENT);
}

void RLApp::faEquivalence()
{
	notify(NULL, FA_EQUIVALENCE);
}

void RLApp::faDeterminization()
{
	notify(NULL, FA_DETERMINIZATION);
}

void RLApp::faMinimization()
{
	notify(NULL, FA_MINIMIZATION);
}

void RLApp::faInsertTransitionName()
{
	fa_model->insertColumn(fa_model->getTerminals().size());
	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->hide();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void RLApp::faRemoveTransitionName()
{
	fa_model->removeColumn(1);
	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->hide();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void RLApp::faInsertTransition()
{
	fa_model->insertRow(fa_model->getStates().size());
	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->hide();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void RLApp::faRemoveTransition()
{
	//fa_model->removeRow(1);
	//ui.table_fa->show();
	//ui.table_fa->verticalHeader()->hide();
	//ui.table_fa->horizontalHeader()->hide();
	//ui.table_fa->resizeColumnsToContents();
	//ui.table_fa->resizeRowsToContents();

	fa_model->insertColumn(0);
	fa_model->insertColumn(1);
	fa_model->insertColumn(2);

	fa_model->insertRow(0);
	fa_model->insertRow(1);
	fa_model->insertRow(2);
}

void RLApp::callAddFAStatesWindow()
{
	_add_fa_terminals_w->show();
}

void RLApp::callAddFATerminWindow()
{
}
