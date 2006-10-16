#include "TLCDController.h"

TLCDController::TLCDController() : QThread() {
	menuDisplayText.setDevice( &menuDisplaySocket );
	i = new QStringListIterator(lcdLines);
	connect(&menuDisplaySocket, SIGNAL(connected()), this, SLOT(connectedToLCDServer()) );
	connectToLCDServer("localhost", 13666);
	this->start();
}

void TLCDController::connectToLCDServer(QString host, int port) {
	menuDisplaySocket.connectToHost(host,port);
}

void TLCDController::connectedToLCDServer() {
	menuDisplayText << "hello\r\n";
	menuDisplayText << "client_set name zmp3\r\n";
	menuDisplayText << "screen_add 0\r\n";
	menuDisplayText << "screen_set 0 heartbeat on\r\n";
	menuDisplayText << "widget_add 0 0 string\r\n";
	menuDisplayText << "widget_add 0 1 string\r\n";
	menuDisplayText << "widget_add 0 2 string\r\n";
	menuDisplayText << "widget_add 0 3 string\r\n";
	menuDisplayText.flush();
	showStartSplash();
}

void TLCDController::showStartSplash() {
	menuDisplayText << "widget_set 0 0 1 1 \"********************\"\r\n";
	menuDisplayText << "widget_set 0 1 1 2 \"*       zmp3       *\"\r\n";
	menuDisplayText << "widget_set 0 2 1 3 \"*by  Sebastian Just*\"\r\n";
	menuDisplayText << "widget_set 0 3 1 4 \"********************\"\r\n";
	menuDisplayText.flush();
}

void TLCDController::run() {

	while(true) {
		QThread::usleep(1000000);//entspricht einer sekunde
	}
}

void TLCDController::appendLine(QString line) {
	lcdLines << line;
}

void TLCDController::setLine(QString line, int lineNr) {

}

void TLCDController::showLine(int line) {

}

void TLCDController::moveMenuDown() {
	if (i->hasNext()) {
		i->next();
	}
	refreshDisplay();
}

void TLCDController::moveMenuUp() {
	if (i->hasPrevious()) {
		i->previous();
	}
	refreshDisplay();
}


void TLCDController::refreshDisplay() {
	QStringListIterator iCopy= *i;
	QString line1 = iCopy.next();
	QString line2 = iCopy.next();
	QString line3 = iCopy.next();
	QString line4 = iCopy.next();
	menuDisplayText << "widget_set 0 0 1 1 \"" + line1 + "\"\r\n";
	menuDisplayText << "widget_set 0 1 1 2 \"" + line2 + "\"\r\n";
	menuDisplayText << "widget_set 0 2 1 3 \"" + line3 + "\"\r\n";
	menuDisplayText << "widget_set 0 3 1 4 \"" + line4 + "\"\r\n";
	menuDisplayText.flush();
}
