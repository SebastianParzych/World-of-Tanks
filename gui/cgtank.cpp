#include "cgtank.h"

#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <QDebug>
#include "cgshell.h"
#include <qrandom.h>
#include <gui\cgimprovements.h>

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;
CGTank::CGTank(CTank *tank): tank(tank), tankAngle(tank->get_RotationXY()),
                turretAngle(tank->get_TurretRotation()),
                Direction(turretAngle),speed(0)
{
    if(get_Player()){ // Initialize base color for tank
         setFlags(QGraphicsItem::ItemIsFocusable); // Make tank controllable
         setFocus();      
         body=QColor(128,102,0);
         turret=QColor(128, 102, 0);
         canister=QColor(47, 93, 22);
         gun=QColor(128, 102, 0);
         cupola=QColor(0, 51, 0);
         fenders=QColor(51, 102, 0);

    }else{
        if(!tank->get_visible()) this->setVisible(false);
        body=QColor(204, 0, 0);
        turret=QColor(204, 41, 0);
        canister=QColor(153, 0, 0);
        gun=QColor(153, 51, 0);
        cupola=QColor(102, 0, 0);
        fenders=QColor(153, 51, 0);
    }
     setPos(tank->get_pos_x(),tank->get_pos_y());
     setRotation(Direction);
     tank->set_explosion_time(0);
}

CGTank::CGTank(int tanktype)
{
    setFlags(QGraphicsItem::ItemIsFocusable); // Make tank controllable
    setFocus();
    body=QColor(128,102,0);
    turret=QColor(128, 102, 0);
    canister=QColor(47, 93, 22);
    gun=QColor(128, 102, 0);
    cupola=QColor(0, 51, 0);
    fenders=QColor(51, 102, 0);
    tank=new CTank(tanktype);
    tankAngle=tank->get_RotationXY();
    turretAngle=tank->get_TurretRotation();
    Direction=turretAngle;
}

void CGTank::advance(int step)
{
    QList <QGraphicsItem*> items=scene()->collidingItems(this); // checking collisions
    tank->Collision_detection(items);

    double x=tank->get_pos_x();
    double y=tank->get_pos_y();
    if(tank->get_Player()){

   this->Direction=tank->get_RotationXY()+90;
   setRotation(Direction);
   setPos(x,y);
    }else{
        if(tank->get_visible()){
            this->setVisible(true);
        }
        else{
            this->setVisible(false);
            }
        setRotation(tank->get_RotationXY()+90);
        setPos(x,y);
    }
}

QRectF CGTank::boundingRect() const
{
    qreal adjust = 0.5;
    switch(tank->get_TankType()){
    case 0:
        return QRectF(-10 - adjust, -22 - adjust,
                      40 + adjust, 50 + adjust);
    case 1:
        return QRectF(-10 - adjust, -22 - adjust,
                      32 + adjust, 50 + adjust);

    case 2:
        return QRectF(-10 - adjust, -22 - adjust,
                      30 + adjust, 45 + adjust);
    }
}

QPainterPath CGTank::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void CGTank::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    switch (tank->get_TankType()) {
    case 0:
        if(tank->get_wreck()){
             painter->setBrush(Qt::black);
             painter->drawEllipse(-30, -35,80,80); // gun
        }
        painter->setBrush(body); // body of tank
        painter->drawRect(-10, -22, 40, 50);


        painter->setBrush(body); // detail
        painter->drawRect(-10, 25,40, 10);

        painter->setBrush(canister);
        painter->drawRect(-8,-23,38,15); // canister on back of tank
        painter->setBrush(Qt::VerPattern);
        painter->drawRect(-8,-23,38,15);
        painter->setBrush(fenders);
        painter->drawRect(-11,-22,7,57); // 1st fender
        painter->drawRect(25,-22,7,57); // 2nd fender

        painter->translate(10,3); // Turret components
        painter->rotate(tank->get_TurretRotation());

        painter->setBrush(gun);
        painter->drawRect(-3,12,7,40); // gun
        painter->drawRect(-4,45,9,6); // gun parts
        painter->drawRect(-4,34,9,6);
        painter->drawRect(-6,15,15,6);


        painter->setBrush(turret);
        painter->drawEllipse(-16,-16,32,32);
        painter->setBrush(Qt::DiagCrossPattern);
        painter->drawEllipse(-12,-10,25,25);// turret
        if(clock()-tank->get_explosion_time()<600){
             painter->setBrush(Qt::blue);
        }else {
            painter->setBrush(turret);
            tank->set_explosion_time(0);
            }
        painter->drawEllipse(-1,-5,15,15); // cupola

        break;
    case 1:
        if(tank->get_wreck()){
             painter->setBrush(Qt::black);
             painter->drawEllipse(-30, -30,70,70); // gun
        }
        painter->setBrush(body); // body of tank
        painter->drawRect(-10, -22, 32, 50);


        painter->setBrush(body); // detail
        painter->drawRect(-10, 15,30, 5);

        painter->setBrush(canister);
        painter->drawRect(-8,-18,25,5); // tank on back of tank

        painter->setBrush(fenders);
        painter->drawRect(-10,-22,7,52); // 1st fender
        painter->drawRect(15,-22,7,52); // 2nd fender

        painter->translate(6,3); // Turret components
        painter->rotate(tank->get_TurretRotation());

        painter->setBrush(gun);
        painter->drawRect(-3,12,5,35); // gun
        painter->drawRect(-4,43,7,10); // gun outlet
        painter->drawRect(-4,27,7,7); // gun
         painter->drawRect(-4,20,7,7); // gun

        painter->setBrush(turret);
        painter->drawEllipse(-13.5,-15,25,35);
        painter->drawRect(-1,-10,10,10);// turret
        painter->drawRect(-11,-10,10,10);// turret
           painter->drawRect(-13.5,-15,15,10);// turret
        if(clock()-tank->get_explosion_time()<600){
             painter->setBrush(Qt::blue);
        }else {
            painter->setBrush(turret);
            tank->set_explosion_time(0);
            }
        painter->drawRect(-1,5,10,10); // cupola


        break;
    case 2:
        if(tank->get_wreck()){
             painter->setBrush(Qt::black);
             painter->drawEllipse(-25, -30,60,60); // gun
        }
        painter->setBrush(body); // body of tank
        painter->drawRect(-10, -20, 30, 40);


        painter->setBrush(body); // detail
        painter->drawRect(-10, 15,30, 5);

        painter->setBrush(canister);
        painter->drawRect(-8,-18,25,5); // tank on back of tank

        painter->setBrush(fenders);
        painter->drawRect(-11,-22,5,44); // 1st fender
        painter->drawRect(16,-22,5,44); // 2nd fender

        painter->translate(6,3); // Turret components
        painter->rotate(tank->get_TurretRotation());

        painter->setBrush(gun);
        painter->drawRect(-3,12,5,30); // gun

        painter->setBrush(gun);
        painter->drawRect(-4,40,7,4); // gun outlet

        painter->setBrush(turret);
        painter->drawEllipse(-13.5,-13,25,25);
        painter->drawRect(-7,-10,12,18);// turret
        if(clock()-tank->get_explosion_time()<400){
             painter->setBrush(Qt::blue);
        }else {
            painter->setBrush(turret);
            tank->set_explosion_time(0);
            }
        painter->drawEllipse(-1,-5,10,10); // cupola
        break;
    }

    if(this->getTank()->get_CurHealth()<=0){
        body=QColor(115, 115, 115);
        turret=QColor(115, 115, 115);
        canister=QColor(89, 89, 89);
        gun=QColor(89, 89, 89);
        cupola=QColor(89, 89, 89);
        fenders=QColor(89, 89, 89);
        }
}

























