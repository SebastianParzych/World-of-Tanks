#include "logic\ctank.h"
#include <QtMath>
#include <qDebug>
#include <QRandomGenerator>
#include <logic\cmap.h>
#include <cmath>
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
static qreal normalizeAngle(qreal angle)
{
    if (angle >= 360)
        angle =0;
    else if (angle <= -360)
        angle= 0;

    return angle;
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
        this->PowerPerTone=13.6;
        this->TurretSpeed=2;
        this->ammo=50;
        this->armor=200;
        this->dmg=390;
        this->reload_time=6;
        this->penetration=219;
        this->Shell_speed=12;
        this->view_range=300;
        break;
    case 1: // Medmium
        this->MAX_HEALTH=1500;
        this->CUR_HEALTH=1500;
        this->speed=4;
        this->reverse_speed=2.5;
        this->RotationSpeed=3.5;
        this->PowerPerTone=13.6;
        this->TurretSpeed=2;
        this->ammo=50;
        this->armor=200;
        this->dmg=390;
        this->reload_time=6;
        this->penetration=219;
        this->Shell_speed=12;
        this->view_range=400;
        break;
    case 2: // Light
        this->MAX_HEALTH=1500;
        this->CUR_HEALTH=1500;
        this->speed=6;
        this->reverse_speed=3;
        this->RotationSpeed=4;
        this->PowerPerTone=13.6;
        this->TurretSpeed=2;
        this->ammo=50;
        this->armor=200;
        this->dmg=390;
        this->reload_time=6;
        this->penetration=219;
        this->Shell_speed=12;
        this->view_range=500;
        break;
    }
}

void CTank::move()
{
    int decision=0;
    bool old_enemy=false;
    angle=(normalizeAngle(RotationXY))*M_PI/180;
    double dx = cos(angle)*1;
    double dy = sin(angle)*1;
    std::deque<ICObject*> neighbors=FMap->getObjectInRange(this);
    ICObject*enemy;
    double closest=2000;
    if(!neighbors.empty()){
        for (ICObject* object: neighbors) {
            if((dynamic_cast<CTank*>(object)) and !dynamic_cast<CTank*>(object)->get_wreck()){
                decision=2;
                double curr_distance=get_distance(object->getPos_X(),object->getPos_Y(),0,0);
                if(curr_distance< closest){
                    closest=object->get_distance(pos_x,pos_y,0,0);
                    enemy=object;
                }
            }
            if(static_cast<CTank*>(object)== closest_enemy) old_enemy=true;
        }
        if(closest_enemy == nullptr or !old_enemy) closest_enemy = static_cast<CTank*>(enemy);
        if(closest_enemy->get_wreck()) {
            closest_enemy=nullptr;
            decision=0;
        }
    }else{
        closest_enemy= nullptr;
        decision=0;
    }

        switch (decision){
        case 0:  // normal move
        {
            if(pos_x+5>=1625){
                RotationXY=normalizeAngle(RotationXY+1*RotationSpeed);
            }
            if(pos_x-5<=-160){
                RotationXY=normalizeAngle(RotationXY+1*RotationSpeed);
            }
            if(pos_y+5<=35){
                RotationXY=normalizeAngle(RotationXY+1*RotationSpeed);
            }
            if(pos_y-5 >= 845){
                RotationXY=normalizeAngle(RotationXY+1*RotationSpeed);
            }
            this->pos_x+=-dx*speed;
            this->pos_y+=-dy*speed;
            //RotationXY=normalizeAngle(RotationXY +1*RotationSpeed);
        }

            break;
        case 1: // grab improvement
        {



        }
            break;
        case 2:     // focus on enemy
        {
            double x1 = pos_x-closest_enemy->getPos_X();
            double y1=  pos_y - closest_enemy->getPos_Y();

            double angle=qAtan2(y1,x1)*180/M_PI; // angle between points
            if( abs(RotationXY-angle)<=10){

            }
            double Direction=RotationXY+TurretRotation; // resultant angle of turret
            int x=0; // Default Turret  Direction

            if(normalizeAngle(Direction) - angle <= -1 )x=1;
            else if(normalizeAngle(Direction) - angle > 1) x=-1;
            TurretRotation=normalizeAngle(TurretRotation+x*TurretSpeed);
            if(normalizeAngle(Direction)-angle <2) {
                shot();
            }
        }
            break;
        }
}
void CTank::move( int y, int rotation, int  turretRotation)
{
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
            set_wreck(true);
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






