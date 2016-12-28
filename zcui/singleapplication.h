#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QApplication>
#include "global.h"

#define SINGLEAPPLICATION

class QLocalServer;

class CUI_API SingleApplication : public QApplication
{
    Q_OBJECT

public:
    explicit SingleApplication(int &argc, char **argv);
	virtual ~SingleApplication();

    bool isRunning();
	void setWindow(QWidget *w);

protected:
	virtual void loading();
	virtual void activateWindow();

private slots:
    void newLocalConnect();

private:
    QLocalServer *m_pServer;
    bool m_bIsRunning;

	QWidget *m_window;
};

#endif // SINGLEAPPLICATION_H
