#ifndef CTANK_H
#define CTANK_H

#include "cshell.h"
#include "gui\cgshell.h"
#include "icmovableobject.h"
#include <QTimer>
#include "cimprovements.h"
class CTank: public ICMovableObject
{
public:
    CTank(int TankType);
    CTank(int TankType, bool isplayer);
    ~CTank(){
        qDebug()<<"CTank destroyed";
    };
    void SetParams(int TankType);
    void move () override ;
    void move ( int y,int rotation, int turretRotation);
    void shot();
    void update() override;
    void Collision_detection(QList <QGraphicsItem*> items) override;
    void set_TankType(int TankType){ this->TankType=TankType;}
    int get_TankType(){   return TankType;}
    void set_Player(bool player){    this->player=player;}
    bool get_Player() {   return this->player;}
    int get_MaxHealth(){return this->MAX_HEALTH;}
    int get_CurHealth(){return this->CUR_HEALTH;}
    void set_CurHealth(int health);
    int get_Shells(){return this->ammo;}
    qreal get_TurretRotation(){return this->TurretRotation;}

    CShell* get_shell(){ return this->shell;}
    int collision_mov(double x , double y); // when QgraphicsItem detec collision witth eg. tank can not move foward.
    void reset_limitations();
    QMap<QString, float> getTankStats();
    void avoid_collision(ICObject* enemy, float dx, float dy);
    void set_wreck(bool wreck){this->wreck=wreck;}
    bool get_wreck(){return wreck;}
    void manage_improv(CImprovements *improv);
private:
    bool wreck=false;
    CTank *focused_enemy;
    QMap <int,bool> limitations;
    bool player=false;
    CShell *shell;
    CGShell *gshell;
    int MAX_HEALTH;
    int CUR_HEALTH;
    int TankType;
    qreal TurretRotation;
    qreal TurretSpeed;
    qreal Shell_speed;
    float PowerPerTone;
    int armor;
    float RotationSpeed;
    float reverse_speed;
    int ammo;
    float reload_time;
    int penetration;
    int points;
    int last_shot=0;
    int curr_reload=0;
};

#endif // CTANK_H
