#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_NewFA.h"

#include "util/Subject.h"
#include "model/FADataModel.h"

class NewFAWindow : public QDialog, public Subject
{
	Q_OBJECT

public:
	NewFAWindow(QWidget *parent = Q_NULLPTR);

	void setDataModel(FADataModel* data_model);


	public slots:
	void updateFAModel();
	void cleanLineField();
	void faInsertTransitionName();
	void faRemoveTransitionName();
	void faInsertTransition();
	void faRemoveTransition();
	void faSetFinalState();
	//void addProduction();
	//void removeProductionName();
	//void removeProduction();
	//void acceptedGrammar();

private:
	FADataModel* fa_model;
	Ui::NewFA ui;
};
