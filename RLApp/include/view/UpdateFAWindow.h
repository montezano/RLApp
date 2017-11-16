#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UpdateFA.h"

#include "util/Subject.h"
#include "model/FADataModel.h"

class UpdateFAWindow : public QDialog
{
	Q_OBJECT

public:
	UpdateFAWindow(QWidget *parent = Q_NULLPTR);

	void setDataModel(FADataModel* data_model);


	public slots:
	void addProductionName();
	void cleanLineField();
	//void addProduction();
	//void removeProductionName();
	//void removeProduction();
	//void acceptedGrammar();

private:
	Ui::UpdateFA ui;
};
