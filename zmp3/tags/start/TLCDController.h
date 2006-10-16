#include <QThread>
#include <QStringList>
#include <QStringListIterator>
#include <QTcpSocket>
#include <QTextStream>

class TLCDController : QThread{
Q_OBJECT
   private:
	QTcpSocket menuDisplaySocket;
	QTextStream menuDisplayText;
	QStringList lcdLines;
	QStringListIterator* i;

	void connectToLCDServer(QString host, int port);
	void showStartSplash();
	void run();
	void refreshDisplay();
   public:
	TLCDController();
	void appendLine(QString line);
	void setLine(QString line, int lineNr);

	void moveMenuDown();
	void moveMenuUp();
	void showLine(int line);

   public slots:
	void connectedToLCDServer();
};
