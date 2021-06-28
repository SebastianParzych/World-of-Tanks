#include "logic\ctank.h"
#include <QtMath>
#include <qDebug>
#include <QRandomGenerator>
#include <logic\cmap.h>
#include <cmath>
#include "gui/cggrass.h"
#include "gui/cgimprovements.h"
#include "gui/cgtank.h"
constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;


CTank::CTank(int TankType) {
    set_RotationXY(QRandomGenerator::global()->bounded(0,360));
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
    set_RotationXY(QRandomGenerator::global()->bounded(0,360));
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
    set_angle((normalizeAngle(get_RotationXY()))*M_PI/180);
    double dx = cos(get_angle())*1;
    double dy = sin(get_angle())*1;
    std::deque<ICObject*> neighbors=get_Map()->getObjectInRange(this);
    ICObject*enemy;
    double closest=2000;
    if(get_pos_x()>1800 or get_pos_x()<40 or get_pos_y()<40 or  get_pos_y()>835){ // force to back to map
        decision = 0 ;
    }else if(!neighbors.empty()){
        for (ICObject* object: neighbors) {
            if((dynamic_cast<CTank*>(object) )){
                double curr_distance=get_distance(object->get_pos_x(),object->get_pos_y(),0,0);
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
        double x1 = get_pos_x()-get_Map()->get_Height()/2;
        double y1=  get_pos_y()-get_Map()->get_Width()/2;
        double angle=qAtan2(y1,x1)*180/M_PI;
        if((normalizeAngle(get_RotationXY()+1) - angle) <- 30 )x=1;
        else if((normalizeAngle(get_RotationXY()-1) -angle) > 30) x=-1;
        else{
            avoid_collision( enemy,   dx,  dy);
        }
        set_RotationXY(normalizeAngle(get_RotationXY()+x*RotationSpeed));
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
        double x1 = get_pos_x()-focused_enemy->get_pos_x();
        double y1=  get_pos_y() - focused_enemy->get_pos_y();
        double angle=qAtan2(y1,x1)*180/M_PI; // angle between points
        double Direction=get_RotationXY()+TurretRotation; // resultant angle of turret
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
        set_pos_xy(get_pos_x()-dx*get_speed(),get_pos_y()-dy*get_speed());
    }else{
        double x1 = get_pos_x()-enemy->get_pos_x();
        double y1=  get_pos_y()-enemy->get_pos_y();
        double angle=qAtan2(y1,x1)*180/M_PI; // angle between points
        if(enemy->get_distance(get_pos_x(),get_pos_y(),0,0)>100){
            set_pos_xy(get_pos_x()-dx*get_speed(),get_pos_y()-dy*get_speed());
        } else if( normalizeAngle(abs(get_RotationXY()-angle))<60){
            if(limitations[1])set_RotationXY(normalizeAngle(get_RotationXY()+1*RotationSpeed));
            if(!limitations[1] and enemy->get_distance(get_pos_x(),get_pos_y(),0,0)<100){
                set_pos_xy(get_pos_x()+dx*reverse_speed,get_pos_y()+dy*reverse_speed);
            }
        }else{
            if(!limitations[0] or abs(enemy->get_distance(get_pos_x(),get_pos_y(),0,0))<100){
                set_pos_xy(get_pos_x()-dx*get_speed(),get_pos_y()-dy*get_speed());
            }
        }
    }

}

void CTank::move( int y, int rotation, int  turretRotation)
{
    if(wreck) return;
    set_angle((normalizeAngle(get_RotationXY()))*M_PI/180);
    switch(y){
    case 1: // go reverse
        if(limitations[0]){
            set_pos_xy(get_pos_x()+cos(get_angle())*reverse_speed,get_pos_y()+sin(get_angle())*reverse_speed);
        }
        break;
    case -1: // go straight foward
        if(limitations[1]){
            set_pos_xy(get_pos_x()-cos(get_angle())*get_speed(),get_pos_y()-sin(get_angle())*get_speed());
        }
        break;
    }
    set_RotationXY(normalizeAngle(get_RotationXY()+rotation*RotationSpeed));
    this->TurretRotation=normalizeAngle(TurretRotation+turretRotation*TurretSpeed);
}

void CTank::collision_mov(double x, double y)
{
    float distance =get_distance(x,y,0,0);
    set_angle((normalizeAngle(get_RotationXY()))*M_PI/180);
    double dx = cos(get_angle())*5;
    double dy = sin(get_angle())*5;
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
    shell= new CShell(get_pos_x(),get_pos_y(),get_RotationXY(),TurretRotation,penetration,get_dmg(),Shell_speed);
    gshell= new CGShell(shell);
    this->get_Map()->addObj(shell);
    this->get_Map()->addObjToDraw(gshell);
    shell->set_Map(get_Map());
    last_shot=clock();
}
void CTank::Collision_detection(QList<QGraphicsItem *> items)
{
    foreach(QGraphicsItem *item,items){
        if(item == dynamic_cast<CGShell*>(item)){
            if(this->get_shell()== static_cast<CGShell*>(item)->get_Shell()) continue;// shell is made inside tank, so ignore parent tank
            this->set_collision_shell(true);
        }
        if( item== dynamic_cast<CGImprovements*>(item)){
            CImprovements *improv=static_cast<CGImprovements*>(item)->get_improv();
            if(improv->get_Open()) continue;
            this->manage_improv(improv);
            improv->set_Open(true);
        }
        if(item == dynamic_cast<CGTank*>(item)){
            this->set_collision_tank(true);
            this->collision_mov(item->x(), item->y());
        }

    }

    if(get_collsion_tank()){
        bool release=true;
        foreach(QGraphicsItem *item,items){
            if( item== dynamic_cast<CGTank*>(item) or item == dynamic_cast<CGGrass*>(item)){
                release=false;
                break;
            }
        }
        if(release){
            set_collision_tank(false);
            this->reset_limitations();
        }
    }
}

void CTank::update()
{

    if(wreck) return;
    this->curr_reload=clock()-last_shot;
    get_Map()->getObjectInRange(this);
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
        set_speed(3);
        this->reverse_speed=2;
        this->RotationSpeed=3;
        this->TurretSpeed=2;
        this->ammo=50;
        this->armor=200;
        set_dmg(390);
        this->reload_time=6;
        this->penetration=219;
        this->Shell_speed=12;
        set_View_range(300);

        break;
    case 1: // Medmium
        this->MAX_HEALTH=2000;
        this->CUR_HEALTH=2000;
        set_speed(4);
        this->reverse_speed=2.5;
        this->RotationSpeed=3.5;
        this->TurretSpeed=2;
        this->ammo=50;
        this->armor=175;
        set_dmg(310);
        this->reload_time=6;
        this->penetration=219;
        this->Shell_speed=12;
        set_View_range(400);

        break;
    case 2: // Light
        this->MAX_HEALTH=1500;
        this->CUR_HEALTH=1500;
        set_speed(6);
        this->reverse_speed=3;
        this->RotationSpeed=4;
        this->TurretSpeed=2;
        this->ammo=50;
        this->armor=120;
        set_dmg(210);
        this->reload_time=6;
        this->penetration=219;
        this->Shell_speed=12;
        set_View_range(500);

        break;
    }
}


QMap<QString, float> CTank::getTankStats()
{
    QMap<QString,float> stats;
    stats["Health"]=MAX_HEALTH;
    stats["armor"]=armor;
    stats["speed"]=get_speed();
    stats["Damage"]=get_dmg();
    stats["penetration"]=penetration;
    stats["reload"]=reload_time;
    stats["View range"]=get_View_range();
    stats["Ammo"]=ammo;
    stats["Shell speed"]=Shell_speed;
    stats["Reverse speed"]=reverse_speed;
    stats["Rotation speed"]=get_RotationXY();
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
    {
        double curr_speed = get_dmg();
        double new_speed = curr_speed*improv->get_upgrade();
        set_speed(new_speed);
        if(get_speed()>8){
            set_speed(8);
        }
    }
        return ;
    case 2:
        this->reverse_speed*=improv->get_upgrade();
        if(reverse_speed>5){
            this->reverse_speed=5;
        }
        return;
    case 3:
        this->RotationSpeed*=improv->get_upgrade();
        if(RotationSpeed>6){
            this->RotationSpeed=6;
        }
        return;
    case 4:
        this->ammo*=improv->get_upgrade();
        return;
    case 5:
    {
        double curr_dmg = get_dmg();
        double new_dmg = curr_dmg*improv->get_upgrade();
        set_dmg(new_dmg);
        if(get_dmg()>450){
            set_dmg(450);
        }
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
    {
        double curr_range = get_dmg();
        double new_range = curr_range*improv->get_upgrade();
        set_View_range(new_range);
        if(get_View_range()>1000){
            set_View_range(1000);
        }
    }
        return;
    case 10:
        this->TurretSpeed*=improv->get_upgrade();
        if(TurretSpeed>3){
            TurretSpeed=3;
        }
        return;
    }
}




