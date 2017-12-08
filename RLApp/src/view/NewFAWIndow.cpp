#include "view/NewFAWindow.h"

NewFAWindow::NewFAWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//QObject::connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(updateFAModel()));
	//QObject::connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(cleanLineField()));

	//QObject::connect(ui.btn_add_term, SIGNAL(accepted()), this, SLOT(addProductionName()));
	//QObject::connect(ui.btn_rem_term, SIGNAL(clicked()), this, SLOT(rejected()));
	QObject::connect(ui.btn_add_trans_name, SIGNAL(clicked()), this, SLOT(faInsertTransitionName()));
	QObject::connect(ui.btn_add_trans, SIGNAL(clicked()), this, SLOT(faInsertTransition()));

	QObject::connect(ui.btn_rem_trans, SIGNAL(clicked()), this, SLOT(faRemoveTransition()));
	QObject::connect(ui.btn_rem_trans_name, SIGNAL(clicked()), this, SLOT(faRemoveTransitionName()));
	QObject::connect(ui.btn_set_final, SIGNAL(clicked()), this, SLOT(faSetFinalState()));


}

void NewFAWindow::updateFAModel()
{
	//QString* text = &ui.line_add_term->text();
	//notify((void*)text, FA_ADD_TERMINAL);
	//notify((void*)fa_data, FA_EQUIVALENCE);


}

void NewFAWindow::setDataModel(FADataModel * data_model)
{
	fa_model = data_model;
	ui.table_fa->setModel(data_model);

	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void NewFAWindow::cleanLineField()
{
	//ui.line_add_term->clear();
}

void NewFAWindow::faInsertTransitionName()
{
	fa_model->insertColumn(fa_model->getTerminals().size());
	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void NewFAWindow::faRemoveTransitionName()
{
	fa_model->removeColumn(fa_model->getTerminals().size() - 1);
	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void NewFAWindow::faInsertTransition()
{
	fa_model->insertRow(fa_model->getStates().size());
	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void NewFAWindow::faRemoveTransition()
{
	fa_model->removeRow(fa_model->getStates().size() - 1);
	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void NewFAWindow::faSetFinalState()
{
	fa_model->setFinalState(ui.table_fa->selectionModel()->selectedIndexes()[0].data().toString());
}



//notify((void*)fa_data, FA_EQUIVALENCE);
