#include "RLApp.h"

RLApp::RLApp(QWidget *parent)
	: QMainWindow(parent)
{
	_add_re_window = new AddReWindow();
	_add_rg_window = new AddRgWindow();


	ui.setupUi(this);
	configureCallbacks();
}

RLApp::RLApp(Observer* observer, FADataModel* fa_data, FADataModel* fa_data2, QWidget *parent)
	: QMainWindow(parent),
	fa_model(fa_data),
	fa_model_2(fa_data2)
{
	_add_re_window = new AddReWindow();
	_add_rg_window = new AddRgWindow();
	_update_fa_window = new UpdateFAWindow();
	_new_fa_window = new NewFAWindow();

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

	_update_fa_window->addObserver(this);
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

	QObject::connect(ui.btn_op_add_another_fa, SIGNAL(clicked()), this, SLOT(faAddAnother()));
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

	QObject::connect(ui.btn_op_clear_data, SIGNAL(clicked()), this, SLOT(clearData()));

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

void RLApp::clearData()
{


	fa_model->clearData();
	
	fa_model_2->clearData();


	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void RLApp::onNotify(void * entity, Events event)
{
	switch (event)
	{
	case FA_UPDATE_OPERATION:
		_update_fa_window = new UpdateFAWindow();
		_update_fa_window->addObserver(this);
		_update_fa_window->setDataModel((FADataModel*)entity);
		_update_fa_window->show();

		//fa_model->setData(*(QString*)entity);
		break;
	case RE_EQUIVALENCE_RESULT:
		(*(bool*)entity?ui.lbl_re_equiv_result->setText("true"):
			ui.lbl_re_equiv_result->setText("false"));
		break;
	case FA_NEW:
		_new_fa_window = new NewFAWindow();
		_new_fa_window->setDataModel((FADataModel*)entity);
		_update_fa_window->show();
		break;
	case FA_UPDATE_ORIGINAL:
		fa_model = (FADataModel*)entity;
		if (fa_model != NULL)
		{
			ui.table_fa->setModel(fa_model);
		}
		ui.table_fa->show();
		ui.table_fa->verticalHeader()->hide();
		ui.table_fa->horizontalHeader()->show();
		ui.table_fa->resizeColumnsToContents();
		ui.table_fa->resizeRowsToContents();
		notify((void*)fa_model, FA_ADD);
		break;
	case RG_TO_FA_UPDATE:
		_new_fa_window = new NewFAWindow();
		_new_fa_window->setDataModel((FADataModel*)entity);
		_update_fa_window->show();

		//ui.table_rg->verticalHeader()->hide();
		//ui.table_rg->horizontalHeader()->show();
		//ui.table_rg->resizeColumnsToContents();
		//ui.table_rg->resizeRowsToContents();
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
	QString* ret_str = &ui.line_re_2->text();
	notify((void*)ret_str, RE_UNION);
}

void RLApp::reIntersection()
{
	QString* ret_str = &ui.line_re_2->text();
	notify((void*)ret_str, RE_INTERSECTION);
}

void RLApp::reComplement()
{
	notify((void*)ui.line_re, RE_COMPLEMENT);
}

void RLApp::reEquivalence()
{
	QString* ret_str = &ui.line_re_2->text();
	notify((void*)ret_str, RE_EQUIVALENCE);
}

void RLApp::rgToFa()
{

	QString gr = ui.text_edit_rg->toPlainText();
	QString* p_gr = new QString(gr);
	notify((void*)p_gr, RG_TO_FA);

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

void RLApp::faAddAnother()
{
	//fa_model_2 = new FADataModel();
	_new_fa_window = new NewFAWindow();
	_new_fa_window->setDataModel(fa_model_2);
	_new_fa_window->show();
}

void RLApp::faUnion()
{

	notify((void*)fa_model_2, FA_UNION);
}

void RLApp::faIntersection()
{
	notify((void*)fa_model_2, FA_INTERSECTION);
}

void RLApp::faComplement()
{
	notify(NULL, FA_COMPLEMENT);
}

void RLApp::faEquivalence()
{
	notify((void*)fa_model_2, FA_EQUIVALENCE);
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
