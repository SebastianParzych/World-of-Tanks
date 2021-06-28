#include "cshell.h"
#include <QDebug>
#include "gui/cgtank.h"
#include "gui/cggrass.h"

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

CShell::CShell(int pos_x,int pos_y,qreal TankRotation,qreal TurretRotation,int penetration,int dmg, qreal Shell_speed)
{
    set_View_range(1);
    set_RotationXY(TankRotation);
    set_dmg(dmg);
    this->TurretRotation=TurretRotation;
    this->penetration=penetration;
    this->Shell_speed=Shell_speed;
    set_pos_xy(pos_x,pos_y);
    TankRotation=TankRotation*M_PI/180;
    TurretRotation=TurretRotation*M_PI/180;
    Direction=TankRotation+TurretRotation;
}


void CShell::move()
{

    if(!hit){
    double old_x=get_pos_x();
    double new_x=old_x-cos(Direction)*Shell_speed;
    double old_y=get_pos_y();
    double new_y=old_y-sin(Direction)*Shell_speed;
    set_pos_xy(new_x,new_y);
        if(get_pos_x()>2000 or get_pos_x()<-100 or get_pos_y()<-100 or get_pos_y()>1000){ // force to back to map
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
                set_collision_shell(false);
            }else{
             if(this->get_hit()) continue; // Preventing to be hitted multiple times by shell;
             set_hit(true);
             static_cast<CGTank*>(item)->getTank()->set_CurHealth(-this->get_dmg());
            }
        }
    }
}
