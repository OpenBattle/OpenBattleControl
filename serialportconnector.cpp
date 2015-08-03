#include "serialportconnector.h"

SerialPortConnector::SerialPortConnector(QString port, int baudRate, QObject *parent) :
	IConnector(parent)
{
	this->port = new QSerialPort(port, this);
	this->port->setBaudRate(baudRate);
	this->port->setDataBits(QSerialPort::Data8);
	this->port->setParity(QSerialPort::NoParity);
	this->port->setStopBits(QSerialPort::OneStop);
	connect(this->port, SIGNAL(readyRead()), this, SIGNAL(readyRead()));
	connect(this->port, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(error(QSerialPort::SerialPortError)));
}

SerialPortConnector::~SerialPortConnector()
{
	this->close();
}

QString SerialPortConnector::name()
{
	return this->port->portName();
}

bool SerialPortConnector::open()
{
	return this->port->open(QIODevice::ReadWrite);
}

void SerialPortConnector::close()
{
	this->port->close();
}

QString SerialPortConnector::error()
{
	return this->port->errorString();
}

QByteArray SerialPortConnector::read(qint64 maxlen)
{
	return this->port->read(maxlen);
}

void SerialPortConnector::error(QSerialPort::SerialPortError)
{
	emit IConnector::error(tr("An I/O error occurred while reading the data from port %1, error: %2").arg(this->port->portName()).arg(this->port->errorString()));
}
