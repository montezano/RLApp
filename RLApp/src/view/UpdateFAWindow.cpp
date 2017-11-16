#include "view/UpdateFAWindow.h"

UpdateFAWindow::UpdateFAWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//QObject::connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(addProductionName()));
	//QObject::connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(cleanLineField()));

	//QObject::connect(ui.btn_add_term, SIGNAL(accepted()), this, SLOT(addProductionName()));
	//QObject::connect(ui.btn_rem_term, SIGNAL(clicked()), this, SLOT(rejected()));


}

void UpdateFAWindow::addProductionName()
{
	//QString* text = &ui.line_add_term->text();
	//notify((void*)text, FA_ADD_TERMINAL);
}

void UpdateFAWindow::setDataModel(FADataModel * data_model)
{
	ui.table_fa->setModel(data_model);

	ui.table_fa->show();
	ui.table_fa->verticalHeader()->hide();
	ui.table_fa->horizontalHeader()->show();
	ui.table_fa->resizeColumnsToContents();
	ui.table_fa->resizeRowsToContents();
}

void UpdateFAWindow::cleanLineField()
{
	//ui.line_add_term->clear();
}
