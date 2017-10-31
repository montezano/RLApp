#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RLApp.h"

#include "view\AddReWindow.h"
#include "view\AddRgWindow.h"
#include "util\Subject.h"
#include "util\Observer.h"

class RLApp : public QMainWindow, public Observer, public Subject
{
	Q_OBJECT

public:
	RLApp(QWidget *parent = Q_NULLPTR);
	RLApp(Observer* observer, QWidget *parent = Q_NULLPTR);

	virtual void onNotify(void *data, Events event);


public slots:
	// Window calls
	void callAddREWindow();
	void callAddRGWindow();
	void callAddFAWindow();
	

	// Interface update

	


private:

	Ui::RLAppClass ui;
	AddReWindow* _add_re_window;
	AddRgWindow* _add_rg_window;


};
