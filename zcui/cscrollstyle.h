#ifndef CSCROLLSTYLE_H
#define CSCROLLSTYLE_H

#include <QProxyStyle>
#include "global.h"

class CUI_API CScrollStyle : public QProxyStyle
{

public:
    void drawComplexControl(ComplexControl control,
                            const QStyleOptionComplex * option,
                            QPainter * painter, const QWidget * widget = 0) const;

private:
    void drawScrollbar(ComplexControl control,
                       const QStyleOptionComplex * option,
                       QPainter * painter, const QWidget * widget) const;
};

#endif // CSCROLLSTYLE_H
