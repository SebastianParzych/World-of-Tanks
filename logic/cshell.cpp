#include "cshell.h"
#include <QDebug>
#include "gui/cgtank.h"


constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

CShell::CShell(int pos_x,int pos_y,qreal TankRotation,qreal TurretRotation,int penetration,int dmg, qreal Shell_speed)
{
    width =15;
    height= 15;
    map_corners();
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

void CShell::Collision_detection(QList<QGraphicsItem *> items)
{
    foreach(QGraphicsItem *item,items){
        if(item == dynamic_cast<CGTank*>(item)){
            if(this==static_cast<CGTank*>(item)->getTank()->get_shell()){
                this->collision_shell=false;
            }else{
             if(this->get_hit()) continue; // Preventing to be hitted multiple times by shell;
             set_hit(true);
             static_cast<CGTank*>(item)->getTank()->set_CurHealth(-this->get_Dmg());
            }
        }
    }
}
