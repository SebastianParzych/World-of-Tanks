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



private:
    void  Collision_recived( QList <QGraphicsItem*> items);
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

