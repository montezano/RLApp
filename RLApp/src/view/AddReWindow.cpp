#include "view/AddReWindow.h"

AddReWindow::AddReWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(acceptedRE()));

}

void AddReWindow::acceptedRE()
{
	
	notify((void*)&(ui.lineEdit->text()), Events::ADD_REGULAR_EXPRESSION);

}
