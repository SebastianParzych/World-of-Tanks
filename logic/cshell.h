#ifndef CSHELL_H
#define CSHELL_H
#include <QDebug>
#include "icmovableobject.h"

class CShell: public ICMovableObject
{
public:
    CShell(int pos_x, int pos_y,qreal TankRotation,qreal TurretRotation,int penetration,int dmg, qreal Shell_speed);
    ~CShell(){
     qDebug()<<"CShell deleted";
    }
     void move () override;
     void update() override;
     void set_hit(bool hit){this->hit=hit;}
     bool get_hit(){return hit;}
private:
    bool hit=false;
    int explosion_range;
    qreal TurretRotation;
    float Direction;
    int penetration;
    qreal Shell_speed;
};

#endif // CSHELL_H