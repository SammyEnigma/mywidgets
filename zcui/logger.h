#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QMutex>
#include "global.h"

class Logger : public QObject
{
    Q_OBJECT
public:
	static Logger *instance();
    static void release();

    static void install();
    static void uninstall();

private:
    Logger(QObject *parent = 0);
    ~Logger();
	Logger(const Logger &singleton);
	Logger &operator =(const Logger &other);

private:
	static QMutex _mutex;
	static Logger *_instance;
};

#endif // LOGGER_H
