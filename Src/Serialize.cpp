#include "Borderless.h"

QDataStream &operator>>(QDataStream &in, GameInfo &gameInfo)
{
	in >> gameInfo.name >> gameInfo.windowName >> gameInfo.className >> gameInfo.x >> gameInfo.y >> gameInfo.width >> gameInfo.height;
	return in;
}

QDataStream &operator<<(QDataStream &out, GameInfo &gameInfo)
{
	out << gameInfo.name << gameInfo.windowName << gameInfo.className << gameInfo.x << gameInfo.y << gameInfo.width << gameInfo.height;
	return out;
}

QDataStream &operator>>(QDataStream &in, GameInfo *gameInfo)
{
	in >> gameInfo->name >> gameInfo->windowName >> gameInfo->className >> gameInfo->x >> gameInfo->y >> gameInfo->width >> gameInfo->height;
	return in;
}

QDataStream &operator<<(QDataStream &out, GameInfo *gameInfo)
{
	out << gameInfo->name << gameInfo->windowName << gameInfo->className << gameInfo->x << gameInfo->y << gameInfo->width << gameInfo->height;
	return out;
}