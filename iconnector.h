#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include <QObject>
#include <QByteArray>

class IConnector : public QObject
{
	Q_OBJECT
public:
	explicit IConnector(QObject *parent = 0);
	~IConnector();
	virtual QString name() = 0;
	virtual bool open() = 0;
	virtual QString error() = 0;
	virtual void close() = 0;
	virtual QByteArray read(qint64 maxlen) = 0;
signals:
	void readyRead();
	void error(QString);

public slots:
};

#endif // ICONNECTOR_H
