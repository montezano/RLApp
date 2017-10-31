#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include "RLApp.h"
#include "ui_AddRE.h"
#include "util\Subject.h"

class MainWindow : public Subject
{
public:
	MainWindow();
	~MainWindow();

	int show();

public slots:
	

private:
	RLApp w;

	

};

#endif // !__MAINWINDOW_H__
