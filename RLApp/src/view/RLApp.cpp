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
	_update_fa_window = new UpdateFAWindow();

	initializeObservers(observer);

	ui.setupUi(this);

	configureCallbacks();



	ui.table_fa->setModel(fa_data);

	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void RLApp::initializeObservers(Observer * observer)
{
	_add_re_window->addObserver(observer);
	_add_rg_window->addObserver(observer);

	_add_re_window->addObserver(this);
	_add_rg_window->addObserver(this);
	//_update_fa_window->addObserver(this);
}

void RLApp::configureCallbacks()
{
	QObject::connect(ui.btn_add_re, SIGNAL(clicked()), this, SLOT(reUpdate()));
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
	QObject::connect(ui.btn_set_final, SIGNAL(clicked()), this, SLOT(faSetFinalState()));


	QObject::connect(ui.table_fa, SIGNAL(selectColumn()), this, SLOT(callAddRGWindow()));

	




}


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
	case FA_UPDATE_OPERATION:
		_update_fa_window->setDataModel((FADataModel*)entity);
		_update_fa_window->show();

		//fa_model->setData(*(QString*)entity);
		break;
	}
}

void RLApp::reUpdate()
{
	ui.line_added_re->setText(ui.line_re->text());
	QString* ret_str = &ui.line_added_re->text();
	notify((void*)ret_str, RE_ADD);
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
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void RLApp::faRemoveTransitionName()
{
	fa_model->removeColumn(fa_model->getTerminals().size()-1);
	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void RLApp::faInsertTransition()
{
	fa_model->insertRow(fa_model->getStates().size());
	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void RLApp::faRemoveTransition()
{
	fa_model->removeRow(fa_model->getStates().size()-1);
	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();

	//fa_model->insertColumn(0);
	//fa_model->insertColumn(1);
	//fa_model->insertColumn(2);

	//fa_model->insertRow(0);
	//fa_model->insertRow(1);
	//fa_model->insertRow(2);
}

void RLApp::faSetFinalState()
{
	fa_model->setFinalState(ui.table_fa->selectionModel()->selectedIndexes()[0].data().toString());
}

void RLApp::callAddFAStatesWindow()
{
	//_add_fa_terminals->show();
}

void RLApp::callAddFATerminWindow()
{
}
