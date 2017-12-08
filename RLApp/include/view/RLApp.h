#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RLApp.h"
#include "ui_AddFA.h"

#include "model/FADataModel.h"
#include "view\AddReWindow.h"
#include "view\AddRgWindow.h"
#include "view\AddFaWindow.h"
#include "view/UpdateFAWindow.h"
#include "view/NewFAWindow.h"
#include "util\Subject.h"
#include "util\Observer.h"

#include "model/MapModel.h"

class RLApp : public QMainWindow, public Observer, public Subject
{
	Q_OBJECT

public:
	RLApp(QWidget *parent = Q_NULLPTR);
	RLApp(Observer* observer, FADataModel* fa_data, FADataModel* fa_data2, QWidget *parent = Q_NULLPTR);
	void initializeObservers(Observer* observer);
	void configureCallbacks();

	virtual void onNotify(void *data, Events event);


public slots:
	// Window calls
	void reUpdate();
	void reToFa();
	void reUnion();
	void reIntersection();
	void reComplement();
	void reEquivalence();


	void rgToFa();
	void rgUnion();
	void rgIntersection();
	void rgComplement();
	void rgEquivalence();

	void faAddAnother();
	void faUnion();
	void faIntersection();
	void faComplement();
	void faEquivalence();
	void faDeterminization();
	void faMinimization();
	void faInsertTransitionName();
	void faRemoveTransitionName();
	void faInsertTransition();
	void faRemoveTransition();
	void faSetFinalState();

	void callAddFAStatesWindow();
	void callAddFATerminWindow();
	void callAddRGWindow();
	void callAddFAWindow();

	void clearData();
	

	// Interface update

	


private:

	Ui::RLAppClass ui;
	AddReWindow* _add_re_window;
	AddRgWindow* _add_rg_window;
	AddFaWindow* _add_fa_window;
	Ui::AddFA* _add_fa_state;
	UpdateFAWindow* _update_fa_window;
	NewFAWindow* _new_fa_window;

	FADataModel* fa_model;
	FADataModel* fa_model_2;




	MapModel mapmodel;
	QMap<QString, QList<QString>> map;



};
