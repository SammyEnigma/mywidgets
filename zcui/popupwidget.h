#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include "global.h"

class Indicator : public QWidget
{
public:
    explicit Indicator(QBoxLayout::Direction direction, QWidget *parent = 0);
    ~Indicator();

    void setColor(const QColor &color);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QBoxLayout::Direction m_direction;
    QPointF m_points[4];

    QColor m_color;
    QSize m_size;
};

class CUI_API PopupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PopupWidget(QBoxLayout::Direction direction,
                         QWidget *w, QWidget *parent = 0);
    ~PopupWidget();

    void setWidget(QWidget *w);
    void setColor(const QColor &color);

signals:

public slots:

private:
    QWidget *m_main;
    QWidget *m_target;

    Indicator *m_indicator;
};

#endif // POPUPWIDGET_H
