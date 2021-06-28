#include "cggrass.h"

#include <QStyleOption>

CGGrass::CGGrass(CGrass *wall)
{
    color = QColor(0,0,0);
    this->grass=wall;
    setPos(wall->get_pos_x(),wall->get_pos_y());
}

void CGGrass::advance(int step)
{

}

QRectF CGGrass::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(0- adjust,0 - adjust,
                  30 + adjust, 30 + adjust);
}

QPainterPath CGGrass::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 30, 30);
    return path;
}

void CGGrass::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
        painter->setBrush(QColor(0,100,0)); // wood
        painter->drawEllipse(0,0, 50, 50);

}
