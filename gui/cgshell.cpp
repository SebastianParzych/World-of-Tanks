#include "cgshell.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <QDebug>
#include "cgtank.h"

CGShell::CGShell(CShell *shell)
{
    this->shell=shell;
}

void CGShell::advance(int step)
{
    if(collision_tank){ // after shell destroy, stay in same place for some time
        return;
    }
    int x=shell->getPos_X();
    int y=shell->getPos_Y();
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
    if(collision_tank and  (clock()-explosion_time<125)){
        painter->setBrush(Qt::red);
        painter->drawEllipse(0,0,16,16);
        shell->set_to_delete(true);
        this->set_to_delete(true);
    }else{
        painter->setBrush(Qt::darkYellow) ;
        painter->drawEllipse(0,0,12,12);
        if(this->get_Shell()->get_hit()==true)
        {
              this->hide();
        }

    }
    QList <QGraphicsItem*> items=scene()->collidingItems(this); // checking collisions
    if(!items.isEmpty()){
         Collision_recived(items);
    }

}

void CGShell::Collision_recived( QList <QGraphicsItem*> items)
{
    foreach(QGraphicsItem *item,items){
        if(item == dynamic_cast<CGTank*>(item)){
            if(this->get_Shell()==static_cast<CGTank*>(item)->getTank()->get_shell()){

                this->collision_shell=false;
            }else{
                if(this->get_Shell()->get_hit())continue; // Preventing to be hitted multuple shell multuple times;
            this->get_Shell()->set_hit(true);
            explosion_time = clock();
            this->collision_tank=true;
            static_cast<CGTank*>(item)->getTank()->set_CurHealth(-this->get_Shell()->get_Dmg());
            }
        }

    }
}

