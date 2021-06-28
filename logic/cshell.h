#ifndef CSHELL_H
#define CSHELL_H
#include <QDebug>
#include "icmovableobject.h"

class CShell: public ICMovableObject //! Object of shell, that is made by the tank
{
public:
    //! Shell constructor
    CShell(int pos_x, int pos_y,qreal TankRotation,qreal TurretRotation,int penetration,int dmg, qreal Shell_speed);
     //! Shell deconstructor
    ~CShell(){qDebug()<<"CShell deleted";
    }
     //! Update position of the shell in map
     void move () override;
     //! Update state of the shell in mpa
     void update() override;
     //! Detect if shell has collision with different object
     void Collision_detection(QList <QGraphicsItem*> items) override;
      //! Change value of bolean hit
     void set_hit(bool hit){this->hit=hit;}
     //! Return value of hit
     bool get_hit(){return hit;}
private:
     //! Variable which shows if the other object hitted shell
    bool hit=false;
    //! Variable which shows if the static object hitted shell
    bool collision_static_object=false;
     //! Range of explosion
    int explosion_range;
     //! Information about turret angle of a tank which made the shell
    qreal TurretRotation;
    //! Direction of fly of the shell
    float Direction;
    //! Penetration of the shell
    int penetration;
     //! Speed of shell
    qreal Shell_speed;
};

#endif // CSHELL_H
