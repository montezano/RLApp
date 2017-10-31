#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AddRE.h"

#include "util/Subject.h"

class AddReWindow : public QDialog, public Subject
{
	Q_OBJECT

public:
	AddReWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::AddRE ui;
};
