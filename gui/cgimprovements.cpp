
#include "cgimprovements.h"
#include <QStyleOption>
CGImprovements::CGImprovements(CImprovements *improv)
{
    color = QColor(0,0,0);
    this->improv=improv;
    setPos(improv->getPos_X(),improv->getPos_Y());
}

void CGImprovements::advance(int step)
{

}

QRectF CGImprovements::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(0- adjust,0 - adjust,
                  20 + adjust, 15 + adjust);
}

QPainterPath CGImprovements::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 30, 20);
    return path;
}

void CGImprovements::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{   if(!improv->get_Open()){
        painter->setBrush(QColor(254, 166, 0)); // wood
        painter->drawRect(0,0, 30, 20);

        painter->setBrush(QColor(58, 165, 254)); // detail 1
        painter->drawRect(0, 8, 30,6);

        painter->setBrush(QColor(255, 255, 0)); //golden detail
        painter->drawRect(11, 7, 8,8);
    }else{
        painter->setBrush(QColor(254, 166, 0));  // wood
        painter->drawRect(0,0, 30, 25);
        painter->drawRect(0, -10, 30, 10); // movable part

        painter->setBrush(QColor(50, 50, 50));
        painter->drawRect(0,-3, 30,15); // empty space inside chest

        painter->setBrush(QColor(58, 165, 254));// lower, upper details
        painter->drawRect(0, 8, 30,6);
        painter->drawRect(0, -7, 30,6);

        painter->setBrush(QColor(255, 255, 0)); // golden detail
        painter->drawRect(11, -7, 8,8);
    }

}
