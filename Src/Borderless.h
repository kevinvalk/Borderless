#ifndef BORDERLESS_H
#define BORDERLESS_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QMenu>
#include <QTimer>
#include <QString>
#include <QVector>
#include <QFile>
#include <QCloseEvent>
#include <QDataStream>
#include <QList>
#include "ui_Main.h"
#include "typedef.h"

class GameInfo : public QListWidgetItem
{
public:
	QString name, className, windowName;
	quint32 width, height;
	quint32 x, y;
	QList<quint32> pids;

	GameInfo() : QListWidgetItem(NULL, 1001)
	{


	}

	QVariant data(int role) const
	{
		GameInfo *game = (GameInfo*)this;
		switch(role)
		{
			case Qt::DisplayRole:
				return game->getName();

		}
		return QVariant();
	}

	QString getName()
	{
		if(!name.isEmpty())
			return name;
		if(!windowName.isEmpty())
			return windowName;
		if(!className.isEmpty())
			return className;
		return "Unknown game";
	}
};

QDataStream &operator>>(QDataStream &in, GameInfo &gameInfo);
QDataStream &operator<<(QDataStream &out, GameInfo &gameInfo);
QDataStream &operator>>(QDataStream &in, GameInfo *gameInfo);
QDataStream &operator<<(QDataStream &out, GameInfo *gameInfo);

class Borderless : public QMainWindow
{
	Q_OBJECT

public:
	Borderless(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~Borderless();
	void setWindow(GameInfo *info);

public slots:
	void update();
	void refreshGames();
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
