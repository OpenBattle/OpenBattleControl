#ifndef SERIALPORTCONNECTOR_H
#define SERIALPORTCONNECTOR_H

#include <QIODevice>
#include <QtSerialPort/QtSerialPort>
#include "iconnector.h"

class SerialPortConnector : public IConnector
{
	Q_OBJECT

	QSerialPort* port;
public:
	SerialPortConnector(QString port, int baudRate = QSerialPort::Baud9600, QObject *parent = 0);
	~SerialPortConnector();
	QString name();
	bool open();
	void close();
	QString error();
	QByteArray read(qint64 maxlen);
public slots:
	void error(QSerialPort::SerialPortError);
};

#endif // SERIALPORTCONNECTOR_H
