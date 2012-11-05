#include "Borderless.h"
#include <QtGui/QApplication>

QApplication *application;
int main(int argc, char *argv[])
{
	application = new QApplication(argc, argv);
	Borderless w;
	int ret = application->exec();
	delete application;
	return ret;
}
