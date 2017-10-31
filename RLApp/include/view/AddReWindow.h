#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AddRE.h"

class AddReWindow : public QDialog
{
	Q_OBJECT

public:
	AddReWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::AddRE ui;
};
