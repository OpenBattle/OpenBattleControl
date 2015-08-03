#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDateTime>

class Logger : public QObject
{
	Q_OBJECT
public:
	explicit Logger(QObject *parent = 0);
	~Logger();
	void write(QString data);
signals:
	void log(QString data);
public slots:
};

#endif // LOGGER_H
