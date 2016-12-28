#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QDesktopServices>
#include <QListWidget>
#include <QMenu>
#include <QLabel>

#include "popupwidget.h"
#include "switchbutton.h"
#include "cscrollstyle.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
	p(NULL)
{
    ui->setupUi(this);

    SwitchButton *btn = new SwitchButton;
    layout()->addWidget(btn);

	ui->tableWidget->setStyle(new CScrollStyle);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    if (p == NULL) {
        QMenu *menu = new QMenu;
        menu->setStyleSheet("QMenu::item:selected { color: #BD510B; }");
        menu->addAction("123");
        menu->addAction("123");
        menu->addAction("123");
        menu->addAction("123");
        menu->addAction("123");
        QMenu *m  = new QMenu("465");
        m->setStyleSheet("QWidget { color: #888888; background: transparent;} QMenu::item:selected { color: #BD510B; }");
        m->addAction("123");
        m->addAction("123");
        m->addAction("123");
        menu->addMenu(m);
        p = new PopupWidget(QBoxLayout::TopToBottom, menu);
        //p->setWidget(new QLabel("123456"));
        p->show();
        p->hide();
    }
    p->move(mapToGlobal(ui->pushButton->geometry().bottomLeft()));
    p->show();
}
