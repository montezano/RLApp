#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AddRG.h"

class AddRgWindow : public QDialog
{
	Q_OBJECT

public:
	AddRgWindow(QWidget *parent = Q_NULLPTR);

public slots:
	void addProductionName();
	void addProduction();
	void removeProductionName();
	void removeProduction();

private:
	Ui::AddRG ui;
};
