#include "cgwall.h"

#include <QStyleOption>

CGWall::CGWall(CWall *wall)
{
    color = QColor(0,0,0);
    this->wall=wall;
    setPos(wall->get_pos_x(),wall->get_pos_y());
}

void CGWall::advance(int step)
{

}

QRectF CGWall::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(0- adjust,0 - adjust,
                  30 + adjust, 30 + adjust);
}

QPainterPath CGWall::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 30, 30);
    return path;
}

void CGWall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
        painter->setBrush(QColor(125,125, 125)); // wood
        painter->drawRect(0,0, 30, 30);

}
