#include "cshell.h"
#include <QDebug>


constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

CShell::CShell(int pos_x,int pos_y,qreal TankRotation,qreal TurretRotation,int penetration,int dmg, qreal Shell_speed)
{
    this->view_range=1;
    this->RotationXY=TankRotation;
    this->TurretRotation=TurretRotation;
    this->penetration=penetration;
    this->dmg=dmg;
    this->Shell_speed=Shell_speed;
    this->pos_x=pos_x;
    this->pos_y=pos_y;
    RotationXY=RotationXY*M_PI/180;
    TurretRotation=TurretRotation*M_PI/180;
    Direction=RotationXY+TurretRotation;
}

void CShell::move()
{

    if(!hit){
    this->pos_x+=-cos(Direction)*Shell_speed;
    this->pos_y+=-sin(Direction)*Shell_speed;
        if(pos_x>2000 or pos_x<-100 or pos_y<-100 or pos_y>1000){ // force to back to map
               this->set_to_delete(true);
        }
    }else{
        this->set_to_delete(true);
    }
}

void CShell::update()
{
        move();
}
