#include "logger.h"

#include <QFile>
#include <QTime>
#include <QDebug>
#include <QLocale>
#include <QCoreApplication>

QMutex mutex;

void LogHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QDateTime time = QDateTime::currentDateTime();
    //QString str = time.toString("[yyyy-MM-dd hh:mm:ss ddd] ");
    QString str = time.toString("[hh:mm:ss]");

    switch (type)
    {
    case QtDebugMsg:
        str += "[Debug] ";
        break;
    case QtInfoMsg:
        str += "[Info] ";
        break;
    case QtWarningMsg:
        str += "[Warning] ";
        break;
    case QtCriticalMsg:
        str += "[Critical] ";
        break;
    case QtFatalMsg:
        str += "[Fatal] ";
        break;
    }
    str = str + msg + " " +context.file + QString(" %1 ").arg(context.line) + context.function;
    //str = str + msg ;

    QMutexLocker locker(&mutex);

    QFile outFile(QCoreApplication::applicationDirPath() + "/1.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream ts(&outFile);
    ts << str << endl;
}

QMutex Logger::_mutex;
Logger *Logger::_instance = 0;

Logger *Logger::instance()
{
	if (!_instance) {
		QMutexLocker locker(&_mutex);

		if (!_instance) {
			_instance = new Logger;
		}
	}

	return _instance;
}

Logger::Logger(QObject *parent)
    :QObject(parent)
{

}

Logger::~Logger()
{
	uninstall();
}

void Logger::install()
{
    qInstallMessageHandler(LogHandler);
}

void Logger::uninstall()
{
    qInstallMessageHandler(0);
}

void Logger::release()
{
    if (0 != _instance) {
		QMutexLocker locker(&_mutex);

        delete _instance;
        _instance = 0;
    }
}