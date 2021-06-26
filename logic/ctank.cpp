#include "logic\ctank.h"
#include <QtMath>
#include <qDebug>
#include <QRandomGenerator>
#include <logic\cmap.h>
#include <cmath>
#include "gui/cgimprovements.h"
#include "gui/cgtank.h"
constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;


CTank::CTank(int TankType) {
    this->RotationXY=QRandomGenerator::global()->bounded(0,360);
    this->TurretRotation=0;
    this->set_TankType(TankType);
    this->SetParams(TankType);
    this->points=0;
    last_shot=clock();
    limitations[0]=true;
    limitations[1]=true;
}
CTank::CTank(int TankType, bool isplayer) {
    this->player=isplayer;
    this->RotationXY=QRandomGenerator::global()->bounded(0,360);
    this->TurretRotation=0;
    this->set_TankType(TankType);
    this->SetParams(TankType);
    this->points=0;
    this->player=player;
    last_shot=clock();
    limitations[0]=true;
    limitations[1]=true;
}


void CTank::move()
{
    int decision=1;
    bool old_enemy=false;
    angle=(normalizeAngle(RotationXY))*M_PI/180;
    double dx = cos(angle)*1;
    double dy = sin(angle)*1;
    std::deque<ICObject*> neighbors=FMap->getObjectInRange(this);
    ICObject*enemy;
    double closest=2000;
    if(pos_x>1800 or pos_x<40 or pos_y<40 or pos_y>835){ // force to back to map
        decision = 0 ;
    }else if(!neighbors.empty()){
        for (ICObject* object: neighbors) {
            if((dynamic_cast<CTank*>(object))){
                double curr_distance=get_distance(object->getPos_X(),object->getPos_Y(),0,0);
                if(curr_distance< closest){
                    closest=curr_distance;
                    enemy=object;
                }
                if(!dynamic_cast<CTank*>(object)->get_wreck()) decision=2;

            }
            if(static_cast<CTank*>(object)== focused_enemy) old_enemy=true;
        }
        if(focused_enemy == nullptr or !old_enemy) focused_enemy = static_cast<CTank*>(enemy);
        if(focused_enemy->get_wreck()) {
            focused_enemy=nullptr;
            decision=1;
        }
    }
    switch (decision){
    case 0:  // get back to map
    {
        int x=0;
        double x1 = pos_x-FMap->get_Height()/2;
        double y1=  pos_y-FMap->get_Width()/2;
        double angle=qAtan2(y1,x1)*180/M_PI;
        if((normalizeAngle(RotationXY+1) - angle) <- 30 )x=1;
        else if((normalizeAngle(RotationXY-1) -angle) > 30) x=-1;
        else{
              avoid_collision( enemy,   dx,  dy);
        }
        RotationXY=normalizeAngle(RotationXY+x*RotationSpeed);
    }

        break;
    case 1: // go normal drive
    {
        avoid_collision(enemy,dx,dy);
        if(TurretRotation < 0)TurretRotation=normalizeAngle(TurretRotation+1*TurretSpeed);
        if(TurretRotation > 0)TurretRotation=normalizeAngle(TurretRotation-1*TurretSpeed);

    }
        break;
    case 2:     // focus on enemy
    {
        double x1 = pos_x-focused_enemy->getPos_X();
        double y1=  pos_y - focused_enemy->getPos_Y();

        double angle=qAtan2(y1,x1)*180/M_PI; // angle between points

        double Direction=RotationXY+TurretRotation; // resultant angle of turret
        int x=0; // Default Turret  Direction
        if(normalizeAngle(Direction) - angle <= -1 )x=1;
        else if(normalizeAngle(Direction) - angle > 1) x=-1;
        TurretRotation=normalizeAngle(TurretRotation+x*TurretSpeed);
        if(normalizeAngle(Direction)-angle <2) {
            shot();
        }
        avoid_collision(enemy,dx,dy);

    }
        break;
    }
}
void CTank::avoid_collision(ICObject* enemy, float  dx, float dy)
{
    if(enemy == nullptr){
        this->pos_x+=-dx*speed;
        this->pos_y+=-dy*speed;
    }else{
        double x1 = pos_x-enemy->getPos_X();
        double y1=  pos_y-enemy->getPos_Y();
        double angle=qAtan2(y1,x1)*180/M_PI; // angle between points
        if(enemy->get_distance(pos_x,pos_y,0,0)>100){
            this->pos_x+=-dx*speed;
            this->pos_y+=-dy*speed;
        } else if( normalizeAngle(abs(RotationXY-angle))<60){
            if(limitations[1])RotationXY=normalizeAngle(RotationXY+1*RotationSpeed);
            if(!limitations[1] and enemy->get_distance(pos_x,pos_y,0,0)<100){
                this->pos_x+=dx*reverse_speed;
                this->pos_y+=dy*reverse_speed;
            }
        }else{
            if(!limitations[0] or abs(enemy->get_distance(pos_x,pos_y,0,0))<100){
                this->pos_x+=-dx*speed;
                this->pos_y+=-dy*speed;
            }
        }
    }

}


void CTank::move( int y, int rotation, int  turretRotation)
{
    if(wreck) return;
    angle=(normalizeAngle(RotationXY))*M_PI/180;
    switch(y){
    case 1: // go reverse
        if(limitations[0]){
            this->pos_x+=cos(angle)*reverse_speed;
            this->pos_y+=sin(angle)*reverse_speed;
        }
        break;
    case -1: // go straight foward
        if(limitations[1]){
            this->pos_x+=-cos(angle)*speed;
            this->pos_y+=-sin(angle)*speed;
        }
        break;
    }
    this->RotationXY=normalizeAngle(RotationXY+rotation*RotationSpeed);
    this->TurretRotation=normalizeAngle(TurretRotation+turretRotation*TurretSpeed);
}

int CTank::collision_mov(double x, double y)
{
    float distance =get_distance(x,y,0,0);
    angle=(normalizeAngle(RotationXY))*M_PI/180;
    double dx = cos(angle)*5;
    double dy = sin(angle)*5;
    if(distance>get_distance(x,y,dx,dy)){
        limitations[0]=false;
    }else{
        limitations[1]=false;
    }
}
void CTank::reset_limitations()
{
    limitations[0]=true;
    limitations[1]=true;
}
void CTank::shot()
{
    if(curr_reload < reload_time*1000/3) return;
    this->ammo--;
    shell= new CShell(pos_x,pos_y,RotationXY,TurretRotation,penetration,dmg,Shell_speed);
    gshell= new CGShell(shell);
    qDebug()<<gshell;
    this->FMap->addObj(shell);
    this->FMap->addObjToDraw(gshell);
    shell->set_Map(FMap);
    last_shot=clock();
}
void CTank::Collision_detection(QList<QGraphicsItem *> items)
{
    foreach(QGraphicsItem *item,items){
        if(item == dynamic_cast<CGShell*>(item)){
            if(this->get_shell()== static_cast<CGShell*>(item)->get_Shell()) continue;// shell is made inside tank, so ignore parent tank
            this->collision_shell=true;
        }
        if( item== dynamic_cast<CGTank*>(item)){
            this->collision_tank=true;
            this->collision_mov(item->x(), item->y());
        }
        if( item== dynamic_cast<CGImprovements*>(item)){
            CImprovements *improv=static_cast<CGImprovements*>(item)->get_improv();
            if(improv->get_Open()) continue;
            this->manage_improv(improv);
            improv->set_Open(true);
        }
    }

    if(collision_tank){
                bool release=true;
                foreach(QGraphicsItem *item,items){
                    if( item== dynamic_cast<CGTank*>(item)){
                            release=false;
                            break;
                    }
                }
                if(release){
                     collision_tank=false;
                     this->reset_limitations();
                }
    }
}

void CTank::update()
{
    if(wreck) return;
    this->curr_reload=clock()-last_shot;
    FMap->getObjectInRange(this);
    if(!player){
        move();
    }
}

void CTank::set_CurHealth(int health)
{
    this->CUR_HEALTH+=health;
    if(CUR_HEALTH<=0){ // when it's health down to minimal 0, object is becoming wreck
        CUR_HEALTH =0 ;
        set_wreck(true);
    }
}

void CTank::SetParams(int TankType)
{
    switch (TankType)
    {
    case 0: // Heavy
        this->MAX_HEALTH=2500;
        this->CUR_HEALTH=2500;
        this->speed=3;
        this->reverse_speed=2;
        this->RotationSpeed=3;
        this->TurretSpeed=2;
        this->ammo=50;
        this->armor=200;
        this->dmg=390;
        this->reload_time=6;
        this->penetration=219;
        this->Shell_speed=12;
        this->view_range=300;
        this->height=50;
        this->width=40;
        break;
    case 1: // Medmium
        this->MAX_HEALTH=2000;
        this->CUR_HEALTH=2000;
        this->speed=4;
        this->reverse_speed=2.5;
        this->RotationSpeed=3.5;
        this->TurretSpeed=2;
        this->ammo=50;
        this->armor=175;
        this->dmg=310;
        this->reload_time=6;
        this->penetration=219;
        this->Shell_speed=12;
        this->view_range=400;
        this->height=50;
        this->width=32;
        break;
    case 2: // Light
        this->MAX_HEALTH=1500;
        this->CUR_HEALTH=1500;
        this->speed=6;
        this->reverse_speed=3;
        this->RotationSpeed=4;
        this->TurretSpeed=2;
        this->ammo=50;
        this->armor=120;
        this->dmg=210;
        this->reload_time=6;
        this->penetration=219;
        this->Shell_speed=12;
        this->view_range=500;
        this->height=40;
        this->width=30;
        break;
    }
}


QMap<QString, float> CTank::getTankStats()
{
    QMap<QString,float> stats;
    stats["Health"]=MAX_HEALTH;
    stats["armor"]=armor;
    stats["speed"]=speed;
    stats["Damage"]=dmg;
    stats["penetration"]=penetration;
    stats["reload"]=reload_time;
    stats["View range"]=view_range;
    stats["Ammo"]=ammo;
    stats["Shell speed"]=Shell_speed;
    stats["Reverse speed"]=reverse_speed;
    stats["Rotation speed"]=RotationXY;
    stats["Turret rotation"]=RotationSpeed;
    return stats;
}
void CTank::manage_improv(CImprovements *improv)
{
    switch (improv->get_stat()) {
    case 0:
        this->MAX_HEALTH*=improv->get_upgrade();
        this->CUR_HEALTH*=improv->get_upgrade();
        if(MAX_HEALTH>4000){
            this->MAX_HEALTH*=4000;
            this->CUR_HEALTH*=4000;
        }
        return;
    case 1:
        this->speed*=improv->get_upgrade();
        if(speed>8){
            this->speed=8;
        }
        return ;
    case 2:
            this->reverse_speed*=improv->get_upgrade();
        if(reverse_speed>5){
            this->speed=5;
        }
        return;
    case 3:
            this->RotationSpeed*=improv->get_upgrade();
        if(RotationSpeed>6){
            this->speed=6;
        }
        return;
    case 4:
            this->ammo*=improv->get_upgrade();
        return;
    case 5:
            this->dmg*=improv->get_upgrade();
        if(dmg>450){
            this->dmg=450;
        }
        return;
    case 6:
            this->reload_time*=improv->get_upgrade();
        if(reload_time<3){
            this->reload_time=3;
        }
        return ;
    case 7:
            this->penetration*=improv->get_upgrade();
        if(penetration>350){
            penetration=350;
        }
        return;
    case 8:
            this->Shell_speed*=improv->get_upgrade();
        if(Shell_speed>12){
            Shell_speed=12;
        }
        return;
    case 9:
            this->view_range*=improv->get_upgrade();
        if(view_range>1000){
            view_range=1000;
        }
        return;
    case 10:
            this->TurretSpeed*=improv->get_upgrade();
        if(view_range>3){
            view_range=3;
        }
        return;
    }


}


