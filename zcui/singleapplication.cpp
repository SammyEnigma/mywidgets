#include "singleapplication.h"

#include <QLocalSocket>
#include <QLocalServer>
#include <QFile>
#include <QTextStream>
#include <QWidget>

SingleApplication::SingleApplication(int &argc, char **argv)
    : QApplication(argc, argv),
      m_bIsRunning(false),
	  m_window(NULL)
{
    QCoreApplication::setOrganizationName("_");
    //QCoreApplication::setApplicationName("AppName");
    QString strServerName = QCoreApplication::organizationName() 
    	+ QCoreApplication::applicationName();

    QLocalSocket socket;
    socket.connectToServer(strServerName);

    if (socket.waitForConnected(500)) {
        QTextStream stream(&socket);
        QStringList args = QCoreApplication::arguments();

        QString strArg = (args.count() > 1) ? args.last() : "";
        stream << strArg;
        stream.flush();

        socket.waitForBytesWritten();

        m_bIsRunning = true;
    } else {
        m_pServer = new QLocalServer(this);
        connect(m_pServer,SIGNAL(newConnection()),this,SLOT(newLocalConnect()));

        if (m_pServer->listen(strServerName)) {
            if (m_pServer->serverError() == QAbstractSocket::AddressInUseError) {
                QFile::remove(m_pServer->serverName());
                m_pServer->listen(strServerName);
            }
        }
    }
}

SingleApplication::~SingleApplication()
{

}

void SingleApplication::newLocalConnect()
{
    QLocalSocket *pSocket = m_pServer->nextPendingConnection();
    if (pSocket != NULL) {
        pSocket->waitForReadyRead(1000);

        QTextStream in(pSocket);
        QString strValue;
        in >> strValue;

        qDebug() << QString("the value is : %1").arg(strValue);

        delete pSocket;
        pSocket = NULL;

		activateWindow();
    }
}

void SingleApplication::activateWindow()
{
	if (m_window) {
		m_window->showNormal();
		m_window->activateWindow();
	}
}

void SingleApplication::loading()
{
	qDebug() << "splash for loading...";
}

bool SingleApplication::isRunning()
{
	if (!m_bIsRunning)
		loading();

    return m_bIsRunning;
}

void SingleApplication::setWindow(QWidget *w)
{
	m_window = w;
}