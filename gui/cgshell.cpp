#include "cgshell.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <QDebug>


CGShell::CGShell(CShell *shell)
{
    this->shell=shell;
}

void CGShell::advance(int step)
{
    if(shell->get_hit()){
        this->set_to_delete(true);
    }
    if(shell->get_to_delete()){
           this->set_to_delete(true);
    }
    double x=shell->get_pos_x();
    double y=shell->get_pos_y();
    setRotation(shell->get_RotationXY()+90);
    setPos(x,y);
}

QRectF CGShell::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(0,-2,
                  12 + adjust, 12 + adjust);
}

QPainterPath CGShell::shape() const
{
    QPainterPath path;
    path.addRect(0, 0,12, 12);
    return path;
}
void CGShell::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    if(this->shell->get_hit()){
        painter->setBrush(Qt::red);
        painter->drawEllipse(0,0,16,16);
        this->set_to_delete(true);
    }else{
        painter->setBrush(Qt::darkYellow) ;
        painter->drawEllipse(0,0,12,12);
   }
    QList <QGraphicsItem*> items=scene()->collidingItems(this); // checking collisions
    shell->Collision_detection(items);
}



