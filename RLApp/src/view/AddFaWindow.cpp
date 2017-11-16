#include "view/AddFaWindow.h"

AddFaWindow::AddFaWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//QObject::connect(ui.btn_add_prod_name, SIGNAL(clicked()), this, SLOT(addProductionName()));
	//QObject::connect(ui.btn_add_prod, SIGNAL(clicked()), this, SLOT(addProduction()));
	//QObject::connect(ui.btn_rem_prod_name, SIGNAL(clicked()), this, SLOT(removeProductionName()));
	//QObject::connect(ui.btn_rem_prod, SIGNAL(clicked()), this, SLOT(removeProduction()));
	//QObject::connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(acceptedGrammar()));

}

void AddFaWindow::addProductionName()
{
	//ui.table_rg->insertRow(ui.table_rg->rowCount());
}

void AddFaWindow::addProduction()
{
	//ui.table_rg->insertColumn(ui.table_rg->columnCount());
}

void AddFaWindow::removeProductionName()
{
	//ui.table_rg->removeRow(ui.table_rg->rowCount() - 1);
}

void AddFaWindow::removeProduction()
{
	//ui.table_rg->removeColumn(ui.table_rg->columnCount() - 1);
}

void AddFaWindow::acceptedGrammar()
{
	//notify(NULL, Events::ADD_FINITE_AUTOMATA);
	//ui.line_re
	//ui.
}