#include <QtWidgets/QApplication>
#include "controller/MainController.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainController::run();

	return a.exec();
}
