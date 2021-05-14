#include "cgimprovements.h"

CGImprovements::CGImprovements(CImprovements *improv)
{
    this->improv=improv;
}

void CGImprovements::advance(int step)
{
    int pos_x=improv->getPos_X();
    int pos_y=improv->getPos_Y();
    setPos(pos_x++,pos_y++);
}

QRectF CGImprovements::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}

QPainterPath CGImprovements::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void CGImprovements::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    // Eyes
    painter->setBrush(Qt::black);
    painter->drawEllipse(-8, -10, 20, 20);

}

void CGImprovements::Collision_recived(QList<QGraphicsItem *> items)
{

}
