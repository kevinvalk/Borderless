#ifndef BORDERLESS_H
#define BORDERLESS_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include <QString>
#include <QVector>
#include <QMenu>
#include <QCloseEvent>
#include <QSystemTrayIcon>
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
	QMenu *menu;
	QSystemTrayIcon *tray;
	QVector<GameInfo*> games;
	QTimer *timer;

protected:
	bool event(QEvent *event);
};

extern QApplication *application;
#endif // BORDERLESS_H
