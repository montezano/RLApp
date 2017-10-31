#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RLApp.h"

class RLApp : public QMainWindow
{
	Q_OBJECT

public:
	RLApp(QWidget *parent = Q_NULLPTR);

private:
	Ui::RLAppClass ui;
};
