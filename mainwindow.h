#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QtSerialPort/QtSerialPort>
#include <Generated.h>
#include <OpenBattleCore.h>
#include "iconnector.h"
#include "serialportconnector.h"
#include "logger.h"
#include "informationmessagehandler.h"

using namespace OpenBattle;

namespace Ui {
class MainWindow;
}

class SelectSerialPortAction : public QAction {
	Q_OBJECT

	QString port;
public:
	SelectSerialPortAction(QString port, QString description, QObject *parent = 0);
signals:
	void triggered(QString port);
private slots:
	void triggered();
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

	Logger *logger;
	IConnector* connector = 0;
	Protocol protocol;
	void connectConnector();
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
private slots:
	void populateSerialPorts();
	void selectSerialPort(QString port);
	void readConnector();
	void connectionError(QString error);
	void writeLog(QString message);
private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
