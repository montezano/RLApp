#include "view/AddRgWindow.h"

AddRgWindow::AddRgWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.btn_add_prod_name, SIGNAL(clicked()), this, SLOT(callAddREWindow()));
	QObject::connect(ui.add_grammar_btn, SIGNAL(clicked()), this, SLOT(callAddRGWindow()));
}

void AddRgWindow::addProduction()
{
}

void AddRgWindow::removeProductionName()
{
}

void AddRgWindow::RemoveProduction()
{
}
