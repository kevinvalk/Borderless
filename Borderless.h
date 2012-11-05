#ifndef BORDERLESS_H
#define BORDERLESS_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include <QString>
#include <QVector>
#include <QList>
#include "ui_Main.h"
#include "typedef.h"

struct GameInfo
{
	QString name, className, windowName;
	quint32 width, height;
	quint32 x, y;
	QList<quint32> pids;
};

class Borderless : public QMainWindow
{
	Q_OBJECT

public:
	Borderless(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Borderless();
	void setWindow(GameInfo *info);

public slots:
	void update();

private:
	Ui::BorderlessClass ui;
	QVector<GameInfo*> games;
	QTimer *timer;
};

#endif // BORDERLESS_H
