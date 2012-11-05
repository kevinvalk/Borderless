#ifndef BORDERLESS_H
#define BORDERLESS_H

#include <QtGui/QMainWindow>
#include "ui_Main.h"

class Borderless : public QMainWindow
{
	Q_OBJECT

public:
	Borderless(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Borderless();

private:
	Ui::BorderlessClass ui;
};

#endif // BORDERLESS_H
