#include "cscrollstyle.h"

#include <QPainter>
#include <QStyleOptionSlider>

void CScrollStyle::drawComplexControl(QStyle::ComplexControl control,
                                      const QStyleOptionComplex *option,
                                      QPainter *painter, const QWidget *widget) const
{
    switch (control) {

    case CC_ScrollBar:
        drawScrollbar(control, option, painter, widget);
        return;
    default:
        break;
    }
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

void CScrollStyle::drawScrollbar(QStyle::ComplexControl control,
                                 const QStyleOptionComplex *option,
                                 QPainter *painter, const QWidget *widget) const
{
    const QStyleOptionSlider *scrollbar =
            qstyleoption_cast<const QStyleOptionSlider *>(option);

    if(!scrollbar)
        return;

    bool maxedOut = (scrollbar->maximum == scrollbar->minimum);
    if(maxedOut)
        return;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    QRect r = option->rect;
    const State state = option->state;
    const SubControls sub = option->subControls;

    State flags = option->state;

    if (widget && widget->testAttribute(Qt::WA_UnderMouse)
            && widget->isActiveWindow()) {
        flags |= State_MouseOver;
    }

    QRect drawRect;
    if (maxedOut) {
        flags &= ~State_Enabled;
    }

    const bool pressed = flags & State_Sunken;
    const bool mouseOver = flags & State_MouseOver;
    const bool isHorz = flags & State_Horizontal;
    const bool isRTL  = option->direction == Qt::RightToLeft;

    QColor bkFillColor = Qt::white;
    QColor bkSliderNormal = Qt::lightGray;
    QColor bkSliderHover = Qt::gray;
    QColor bkSliderPress = Qt::darkGray;

    //清除所有子控件背景
    //上下（左右）箭头可能和沟槽的背景不一样
    drawRect= subControlRect(CC_ScrollBar, option, SC_ScrollBarAddLine, widget);
    painter->fillRect(drawRect, bkFillColor);

    drawRect= subControlRect(CC_ScrollBar, option, SC_ScrollBarSubLine, widget);
    painter->fillRect(drawRect, bkFillColor);

    //沟槽的颜色
    drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarGroove, widget);
    painter->fillRect(drawRect, Qt::green);

    //在mouse over状态下，才绘制上下左右箭头。
    //scrollbar->activeSubControls用于指定当前鼠标所在的子控件
    const QStyle::SubControls sc = scrollbar->activeSubControls;
    if(!mouseOver) {
        //只绘制Slider，其余清除
        drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarSlider, widget);

        QPainterPath painterPath;
        painterPath.addRoundedRect(drawRect.left(), drawRect.top(),
                                   drawRect.width(), drawRect.height(), 4, 4);
        painter->fillPath(painterPath, bkSliderNormal);
    } else {
        //合并绘制AddPage SubPage
        drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarGroove, widget);
        painter->fillRect(drawRect, QColor(192, 192, 192, 127));

        //画加号，应该区分水平和垂直
        if (sub & SC_ScrollBarAddLine) {
            drawRect= subControlRect(CC_ScrollBar, option, SC_ScrollBarAddLine, widget);
            QPixmap pixmap;

            if(isHorz) {
                if(pressed)
                    pixmap.load(":/ScrollBar/scrollbar_arrowright_down.png");
                else if(sc & SC_ScrollBarAddLine)
                    pixmap.load(":/ScrollBar/scrollbar_arrowright_highlight.png");
                else
                    pixmap.load(":/ScrollBar/scrollbar_arrowright_normal.png");

            } else {
                if(pressed)
                    pixmap.load(":/ScrollBar/scrollbar_arrowdown_down.png");
                else if(sc & SC_ScrollBarAddLine)
                    pixmap.load(":/ScrollBar/scrollbar_arrowdown_highlight.png");
                else
                    pixmap.load(":/ScrollBar/scrollbar_arrowdown_normal.png");
            }
            painter->drawPixmap(drawRect, pixmap);
        }
        if (sub & SC_ScrollBarSubLine) {
            drawRect= subControlRect(CC_ScrollBar, option, SC_ScrollBarSubLine, widget);
            QPixmap pixmap;
            if(isHorz) {
                if(pressed)
                    pixmap.load(":/ScrollBar/scrollbar_arrowleft_down.png");
                else if(sc & SC_ScrollBarSubLine)
                    pixmap.load(":/ScrollBar/scrollbar_arrowleft_highlight.png");
                else
                    pixmap.load(":/ScrollBar/scrollbar_arrowleft_normal.png");
            } else {
                if(pressed)
                    pixmap.load(":/ScrollBar/scrollbar_arrowup_down.png");
                else if(sc & SC_ScrollBarSubLine)
                    pixmap.load(":/ScrollBar/scrollbar_arrowup_highlight.png");
                else
                    pixmap.load(":/ScrollBar/scrollbar_arrowup_normal.png");
            }
            painter->drawPixmap(drawRect, pixmap);
        }
        if (sub & SC_ScrollBarSlider) {
            drawRect = subControlRect(CC_ScrollBar, option, SC_ScrollBarSlider, widget);
            QPainterPath painterPath;
            painterPath.addRoundedRect(drawRect.left(), drawRect.top(),
                                       drawRect.width(), drawRect.height(), 4, 4);
            if(sc & SC_ScrollBarSlider) {
                painter->fillPath(painterPath, bkSliderPress);
            } else {
                painter->fillPath(painterPath, bkSliderHover);
            }
        }
    }
    painter->restore();
}

