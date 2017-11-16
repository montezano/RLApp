#include "view/AddFATerminalWindow.h"

AddFATerminalWindow::AddFATerminalWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(addProductionName()));
	QObject::connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(cleanLineField()));

	//QObject::connect(ui.btn_add_term, SIGNAL(accepted()), this, SLOT(addProductionName()));
	//QObject::connect(ui.btn_rem_term, SIGNAL(clicked()), this, SLOT(rejected()));


}

void AddFATerminalWindow::addProductionName()
{
	QString* text = &ui.line_add_term->text();
	notify((void*)text, FA_ADD_TERMINAL);
}

void AddFATerminalWindow::cleanLineField()
{
	ui.line_add_term->clear();
}
