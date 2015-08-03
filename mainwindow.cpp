#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->menuSerialPort, SIGNAL(aboutToShow()), this, SLOT(populateSerialPorts()));

	this->logger = new Logger(this);
	connect(this->logger, SIGNAL(log(QString)), this, SLOT(writeLog(QString)));

	REGISTER(this->protocol);

	this->protocol.addHandler(new InformationMessageHandler(this->logger));
}

MainWindow::~MainWindow()
{
	this->connector->close();
	delete ui;
}

void MainWindow::connectConnector()
{
	connect(this->connector, SIGNAL(readyRead()), this, SLOT(readConnector()));
	connect(this->connector, SIGNAL(error(QString)), this, SLOT(connectionError(QString)));
}

void MainWindow::populateSerialPorts()
{
	ui->menuSerialPort->clear();
	QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
	QList<QAction*> actions;
	foreach (const QSerialPortInfo &info, list) {
		SelectSerialPortAction *action = new SelectSerialPortAction(info.portName(), info.description(), ui->menuSerialPort);
		action->setCheckable(true);
		if (this->connector != 0 && this->connector->name() == info.portName()) {
			action->setChecked(true);
		}
		connect(action, SIGNAL(triggered(QString)), this, SLOT(selectSerialPort(QString)));
		actions.append(action);
	}
	ui->menuSerialPort->addActions(actions);
}

void MainWindow::selectSerialPort(QString port)
{
	this->connector = new SerialPortConnector(port, QSerialPort::Baud9600, this);
	if (this->connector->open()) {
		this->connectConnector();
	} else {
		ui->txtDebugLog->append(QString("ERROR: ").append(this->connector->error()).append("\n"));
	}
}

void MainWindow::readConnector()
{
	QByteArray data = this->connector->read(16384);
	for (int i = 0; i < data.length(); i++) {
		this->protocol.consume(data.at(i));
	}
}

void MainWindow::connectionError(QString error)
{
	ui->txtDebugLog->append(error.append("\n"));
}

void MainWindow::writeLog(QString message)
{
	ui->txtDebugLog->append(message);
}

SelectSerialPortAction::SelectSerialPortAction(QString port, QString description, QObject *parent) :
	QAction(port + " (" + description + ")", parent),
	port(port)
{
	connect(this, SIGNAL(triggered()), this, SLOT(triggered()));
}

void SelectSerialPortAction::triggered()
{
	emit this->triggered(this->port);
}
