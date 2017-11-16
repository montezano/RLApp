#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AddFAterminals.h"

#include "util/Subject.h"

class AddFATerminalWindow : public QDialog, public Subject
{
	Q_OBJECT

public:
	AddFATerminalWindow(QWidget *parent = Q_NULLPTR);

	public slots:
	void addProductionName();
	void cleanLineField();
	//void addProduction();
	//void removeProductionName();
	//void removeProduction();
	//void acceptedGrammar();

private:
	Ui::AddFATerminals ui;
};
