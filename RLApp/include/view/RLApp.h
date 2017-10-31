#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RLApp.h"

#include "view\AddReWindow.h"
#include "view\AddRgWindow.h"

class RLApp : public QMainWindow
{
	Q_OBJECT

public:
	RLApp(QWidget *parent = Q_NULLPTR);

public slots:
	void callAddREWindow();
	void callAddRGWindow();
	void callAddFAWindow();


private:
	Ui::RLAppClass ui;
	AddReWindow* _add_re_window;
	AddRgWindow* _add_rg_window;


};
