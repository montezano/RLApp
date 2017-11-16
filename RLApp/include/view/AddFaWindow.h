#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AddFA.h"

#include "util/Subject.h"

class AddFaWindow : public QDialog, public Subject
{
	Q_OBJECT

public:
	AddFaWindow(QWidget *parent = Q_NULLPTR);

	public slots:
	void addProductionName();
	void addProduction();
	void removeProductionName();
	void removeProduction();
	void acceptedGrammar();

private:
	Ui::AddFA ui;
};
