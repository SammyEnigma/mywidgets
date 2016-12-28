#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H


#include <QWidget>
#include "global.h"


class CUI_API SwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = 0);

    void setModal(bool b);
    void reset();
    void setChecked(bool checked);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

signals:
    void pressed();
    void toggled(bool checked);

public slots:
    void toggle();

private:
    QRect clickedRect();

private:
    bool m_pressed;
    bool m_toggled;
    bool m_modal;
};

#endif // SWITCHBUTTON_H
