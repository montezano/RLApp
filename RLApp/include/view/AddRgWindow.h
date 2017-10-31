#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AddRG.h"

#include "util\Subject.h"

class AddRgWindow : public QDialog, public Subject
{
	Q_OBJECT

public:
	AddRgWindow(QWidget *parent = Q_NULLPTR);

public slots:
	void addProductionName();
	void addProduction();
	void removeProductionName();
	void removeProduction();
	void acceptedGrammar();

private:
	Ui::AddRG ui;
};
