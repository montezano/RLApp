#include "RLApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RLApp w;
	w.show();
	return a.exec();
}
