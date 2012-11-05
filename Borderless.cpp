#include "Borderless.h"
#include <Windows.h>

Borderless::Borderless(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// Create the system context menu
	menu = new QMenu(this);
	menu->addAction(tr("Show"), this, SLOT(show()));
	menu->addAction(tr("Close"), application, SLOT(quit()));

	// Create system tray
	tray = new QSystemTrayIcon(QIcon(":/Borderless/icon.png"));
	tray->setContextMenu(menu);
	tray->show();
	
	// Create timed loop
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(50);

	// Setup the games
	GameInfo *towerWars = new GameInfo();
	towerWars->className = "TorqueJuggernaughtWindow";
	towerWars->windowName = "Tower Wars";
	towerWars->x = towerWars->y = 0;
	towerWars->width = 1920;
	towerWars->height = 1080;

	games.push_back(towerWars);
}

Borderless::~Borderless()
{

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
