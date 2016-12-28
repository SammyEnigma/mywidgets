#include "switchbutton.h"

#include <QPainter>
#include <QMouseEvent>

#define COLOR_COLOSE_BORDER QColor(0, 0, 0, 25)
#define COLOR_COLOSE_BG_N QColor(255, 255, 255, 100)
#define COLOR_COLOSE_BG_P QColor(0, 0, 0, 35)
#define COLOR_OPEN_BORDER QColor(0, 184, 0, 200)
#define COLOR_OPEN_BG QColor(0, 184, 0, 200)

SwitchButton::SwitchButton(QWidget *parent)
    : QWidget(parent),
      m_toggled(false),
      m_pressed(false),
      m_modal(false)
{
    setFixedSize(60, 35);
}

void SwitchButton::setModal(bool b)
{
    m_modal = b;
}

void SwitchButton::reset()
{
    m_pressed = false;
    update();
}

void SwitchButton::setChecked(bool checked)
{
    m_toggled = checked;
    emit toggled(m_toggled);
    update();
}

void SwitchButton::mousePressEvent(QMouseEvent *event)
{
    if (m_pressed)
        return;

    QRect roc = clickedRect();
    if (roc.contains(event->pos())) {
        m_pressed = true;
        emit pressed();
        update();
    }
}

void SwitchButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_modal)
        return;

    QRect roc = clickedRect();
    if (roc.contains(event->pos()) || !rect().contains(event->pos())) {
        m_pressed = false;
        m_toggled = !m_toggled;
        emit toggled(m_toggled);
        update();
    }
}

void SwitchButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    float radius = (float)height() / 2;
    float pressedWidthF = (float)height() * 10 / 9;

    QColor bg;
    QPointF center;
    QRectF pressedRectF = rect();
    pressedRectF.setWidth(pressedWidthF);
    pressedRectF.adjust(2, 2, -2, -2);
    if (!m_toggled) {
        bg = m_pressed ? COLOR_COLOSE_BG_P : COLOR_COLOSE_BG_N;
        center = QPointF(radius, radius);
    } else {
        bg = COLOR_OPEN_BG;
        center = QPointF((float)width() - radius, radius);
        pressedRectF.moveLeft((float)width() - pressedWidthF);
    }
    float pressedRadius = pressedRectF.height() / 2;

    painter.save();
    QPen pen;
    pen.setColor(COLOR_COLOSE_BORDER);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.setBrush(bg);
    painter.drawRoundedRect(rect(), radius, radius);
    painter.restore();

    painter.save();
    painter.setPen(COLOR_COLOSE_BORDER);
    painter.setBrush(COLOR_COLOSE_BORDER);
    if (m_pressed) {
        painter.drawRoundedRect(pressedRectF, pressedRadius, pressedRadius);
    } else {
        painter.drawEllipse(center + QPointF(0, 2), radius - 2, radius - 2);
    }
    painter.restore();

    painter.save();
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    if (m_pressed) {
        painter.drawRoundedRect(pressedRectF, pressedRadius, pressedRadius);
    } else {
        painter.drawEllipse(center, radius - 3, radius - 3);
    }
    painter.restore();
}

void SwitchButton::toggle()
{
    m_toggled = !m_toggled;
    update();
}

QRect SwitchButton::clickedRect()
{
    QRect roc = rect();
    roc.setWidth(height());
    if (m_toggled) {
        roc.moveLeft(width() - height());
    }
    roc.adjust(3, 3, -3, -3);
    return roc;
}
