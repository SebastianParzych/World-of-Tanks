#ifndef CGTANK_H
#define CGTANK_H

#include "icgobject.h"
#include <logic\ctank.h>

class CGTank: public ICGObject//! GUI implementation of tank class
{
public:
    //! GUI implementation of tank class
    CGTank(CTank *tank);
    //! GUI implementation of tank class used in main menu to show different tanks
    CGTank(int tanktype);
    ~CGTank(){
            qDebug()<<"CGTank deleted";
    };
    //! Update state of object in map
    void advance (int step)override;
    //! Bounding rect of object
    QRectF boundingRect()  const override;
    //! Shape of object
    QPainterPath shape()  const override;
    //! Look of the object
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
     //! Set tank to gui class
    void setTank (CTank *tank){ this->tank=tank;}
    //! Returns tank object of gui class
    CTank* getTank() const { return this->tank;}
    //! Returns information if tank is controlled by a player
    bool get_Player(){return tank->get_Player();}



private:
    //! Base object, whtich gui class is representing
    CTank *tank;
     //! Tank angle rotation
    qreal tankAngle = 0;
    //! Tank turret angle rotation
    qreal turretAngle=0;
    //! Tank turret angle rotation in radians
    qreal Direction=0;
     //! Basic speed of tank
    qreal speed=5;
     //! Color of turret
    QColor turret;
    //! Color of body
    QColor body;
    //! Color of canister
    QColor canister;
    //! Color of gun
    QColor gun;
     //! Color of cupola
    QColor cupola;
     //! Color of fenders
    QColor fenders;

};

#endif // CGTANK_H

