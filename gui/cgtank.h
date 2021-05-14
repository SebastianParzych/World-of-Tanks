#ifndef CGTANK_H
#define CGTANK_H

#include "icgobject.h"
#include <logic\ctank.h>

class CGTank: public ICGObject
{
public:
    CGTank(CTank *tank); // Constructor used in games.
    CGTank(int tanktype); // Constructor only used to display tanks in menu
    ~CGTank(){
            qDebug()<<"CGTank deleted";
    };
    void advance (int step)override;
    QRectF boundingRect()  const override;
    QPainterPath shape()  const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void setTank (CTank *tank){ this->tank=tank;}
    CTank* getTank() const { return this->tank;}
    bool get_Player(){return tank->get_Player();}

protected:
     void  Collision_recived( QList <QGraphicsItem*> items)override;
private:

    CTank *tank;
    qreal tankAngle = 0;
    qreal turretAngle=0;
    qreal TurretRotatio=0;
    qreal Direction=0;
    qreal speed=5;


    QColor turret;
    QColor body;
    QColor canister;
    QColor gun;
    QColor cupola;
    QColor fenders;

};

#endif // CGTANK_H

////        painter->setPen(Qt::NoPen);
////        painter->drawEllipse(-125,-125,tank->get_View_range(),tank->get_View_range());
//        painter->drawRect(-10, -20, 30, 40);
//        painter->setBrush(QColor(47, 93, 22));
//        painter->drawRect(-8,-18,25,5); // tank on back of tank
//        painter->setBrush(QColor(51, 102, 0));
//        painter->drawRect(-11,-22,5,44); // 1st fender
//        painter->drawRect(16,-22,5,44); // 2nd fender

//        painter->translate(6,3); // Turret components
//        painter->rotate(tank->get_TurretRotation());
//        painter->setBrush(QColor(128, 102, 0));
//        painter->drawRect(-3,12,5,30); // gun
//        painter->setBrush(QColor(128, 102, 0));
//        painter->drawRect(-4,40,7,4); // gun outlet
//        painter->setBrush(collision_shell ? QColor(128, 102, 0) : Qt::red);
//        painter->drawEllipse(-13.5,-13,25,25); // turret
//        painter->setBrush(QColor(0, 51, 0));
//        painter->drawEllipse(-1,-5,10,10); // cupola
//        if(this->getTank()->get_CurHealth()<=0){
//            painter->setBrush(QColor(128, 102, 0));
//            painter->drawRect(-3,12,100,100); // gun
//        }
