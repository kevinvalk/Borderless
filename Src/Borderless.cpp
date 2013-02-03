#include "Borderless.h"
#include <Windows.h>

Borderless::Borderless(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// Create the system context menu
	menu = new QMenu(this);
	menu->addAction(tr("Show"), this, SLOT(show()));
	menu->addAction(tr("Close"), application, SLOT(quit()));

	// Create system tray
	tray = new QSystemTrayIcon(this);
	tray->setIcon(QIcon(":/Borderless/icon.png"));
	tray->setContextMenu(menu);
	tray->show();
	
	// Create timed loop
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(50);

	// Open settings file
	QFile file("settings.dat");
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);

	// Read number of games
	qint32 gameNo = 0;
	in >> gameNo;

	// Read all games
	for(uint32 i = 0; i < gameNo; i++)
	{
		GameInfo *game = new GameInfo();
		in >> game;
		games.push_back(game);
	}

	// Close file
	file.close();

	refreshGames();
}

Borderless::~Borderless()
{
	tray->hide();

	// Open settings
	QFile file("settings.dat");
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file);

	// Set number of saved games
	qint32 gameNo = games.size();
	out << gameNo;

	// Save all games
	GameInfo *game;	
	foreach(game, games)
		out << game;

	// Close file
	file.close();
}

bool Borderless::event(QEvent *event)
{
	
	switch(event->type())
	{
		case QEvent::WindowStateChange:
			if(isMinimized())
				QTimer::singleShot(0, this, SLOT(hide()));
		break;
		case QEvent::Show:
			if(isMinimized())
			{
				showNormal();
				event->ignore();
				return false;
			}
		break;
		case QEvent::Close:
			hide();
			event->ignore();
			return false;
		break;
	}
	return QMainWindow::event(event);
}

void Borderless::refreshGames()
{
	ui.gameList->clear();
	GameInfo *game;
	foreach(game, games)
		ui.gameList->addItem(game);
}

void Borderless::setWindow(GameInfo *info)
{
	dword pid;

	HWND h = FindWindow(info->className.toStdWString().c_str(), info->windowName.toStdWString().c_str());
	GetWindowThreadProcessId(h, &pid);

	// Only when we not yet done this pid
	if(info->pids.indexOf(pid) < 0)
	{
		// Calculate new style
		dword style = GetWindowLong(h, GWL_STYLE) & !(WS_BORDER | WS_DLGFRAME | WS_THICKFRAME);
		dword styleEx = GetWindowLong(h, GWL_EXSTYLE) & !WS_EX_DLGMODALFRAME;

		// Set new style
		SetWindowLong(h, GWL_STYLE, style);
		SetWindowLong(h, GWL_EXSTYLE, styleEx);

		// Set position
		SetWindowPos(h, HWND_TOP, info->x, info->y, info->width, info->height, SWP_SHOWWINDOW);

		// Save the pid
		info->pids.push_back(pid);
	}
}

void Borderless::update()
{
	GameInfo *game;
	foreach(game, games)
		setWindow(game);

}
