#include "popupwidget.h"

#include <QPainter>
#include <QVBoxLayout>

Indicator::Indicator(QBoxLayout::Direction direction, QWidget *parent)
    : QWidget(parent),
      m_direction(direction),
      m_color(Qt::black),
      m_size(QSize())
{

}

Indicator::~Indicator()
{

}

void Indicator::setColor(const QColor &color)
{
    m_color = color;
    update();
}

void Indicator::resizeEvent(QResizeEvent *event)
{
    m_size = this->size();
    if (m_size.width() < m_size.height()) {
        m_size.transpose();
    }
    m_points[0] = QPointF(m_size.width() / 2, 0);
    m_points[1] = QPointF(m_size.width() / 2 - 6, m_size.height());
    m_points[2] = QPointF(m_size.width() / 2 + 6, m_size.height());

//    m_points[0] = QPointF(0, rect().height());
//    m_points[1] = QPointF(rect().width(), rect().height());
//    m_points[2] = QPointF(rect().width() / 2 - 1, rect().height() - 7);
//    m_points[3] = QPointF(rect().width() / 2 + 1, rect().height() - 7);

    QWidget::resizeEvent(event);
}

void Indicator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QPixmap temp(m_size);
    temp.fill(Qt::transparent);
    QPainter pp(&temp);
    pp.setRenderHint(QPainter::Antialiasing);
    pp.setPen(QPen(m_color, 1));
    pp.setBrush(QBrush(m_color));

//    QPainterPath path;
//    path.moveTo(m_points[0]);
//    path.cubicTo(m_points[2], m_points[3], m_points[1]);
//    pp.drawPath(path);

    pp.drawPolygon(m_points, 3);

    QPixmap out(temp);
    qreal angle = 0;
    switch (m_direction) {
    case QBoxLayout::TopToBottom:
        break;
    case QBoxLayout::RightToLeft:
        angle = 90;
        break;
    case QBoxLayout::BottomToTop:
        angle = 180;
        break;
    case QBoxLayout::LeftToRight:
        angle = 270;
        break;
    default:
        break;
    }
    QTransform transform;
    transform.rotate(angle);
    out = temp.transformed(transform);

    p.drawPixmap(rect(), out);
}

PopupWidget::PopupWidget(QBoxLayout::Direction direction, QWidget *w, QWidget *parent)
    : QWidget(parent),
      m_target(w)
{
    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::Popup | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(true);
    setWindowOpacity(0.9);

    m_indicator = new Indicator(direction, this);
    QSize size(12, 6);
    switch (direction) {
    case QBoxLayout::LeftToRight:
    case QBoxLayout::RightToLeft:
        setMinimumHeight(20);
        m_indicator->setFixedSize(size.transposed());
        break;
    case QBoxLayout::TopToBottom:
    case QBoxLayout::BottomToTop:
        setMinimumWidth(20);
        m_indicator->setFixedSize(size);
        break;
    default:
        break;
    }

    m_main = new QWidget;
    m_main->setAutoFillBackground(true);
    m_main->setLayout(new QVBoxLayout);
    m_main->layout()->setSpacing(0);
    m_main->layout()->setContentsMargins(2, 2, 2, 2);
    m_main->layout()->addWidget(m_target);

    m_target->setStyleSheet("color: #888888; background: transparent");

    QBoxLayout *l = new QBoxLayout(direction);
    l->setSpacing(0);
    l->setContentsMargins(0, 0, 0, 0);

    l->addWidget(m_indicator, 0, Qt::AlignHCenter);
    l->addWidget(m_main);
    setLayout(l);

    setColor(Qt::black);
}

PopupWidget::~PopupWidget()
{

}

void PopupWidget::setWidget(QWidget *w)
{
    if (m_target == w)
        return;

    if (m_target && m_main && w) {
        delete m_target;
        m_target = w;
        m_target->setStyleSheet("color: #888888; background: transparent");

        m_main->layout()->addWidget(m_target);
    }
}

void PopupWidget::setColor(const QColor &color)
{
    QPalette palette = m_main->palette();
    palette.setBrush(QPalette::Background, color);
    m_main->setPalette(palette);

    m_indicator->setColor(color);
}

