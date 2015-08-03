#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent)
{
}

Logger::~Logger()
{
}

void Logger::write(QString data)
{
	QDateTime now = QDateTime::currentDateTime();
	emit this->log(now.time().toString("HH:mm:ss.zzz").append(": ").append(data));
}
