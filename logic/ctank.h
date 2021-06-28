#ifndef CTANK_H
#define CTANK_H

#include "cshell.h"
#include "gui\cgshell.h"
#include "icmovableobject.h"
#include <QTimer>
#include "cimprovements.h"
class CTank: public ICMovableObject //! Class of tank, Tank can be player and also an enemy controlled by alghoritms,
                                    //! Tank is recieving improvements if is colliding with one ot them,
                                    //! Each tank controlled by alghoritm, can addapt to current situaion in the map-Simultaneously aim and shoot at the enemy and avoid the nearest obstacles
                                    //! Tank object controlled by player, uses keyboard inputs
{
public:
    //! Tank constructor
    CTank(int TankType);
    CTank(int TankType, bool isplayer);
    //! Tank Deconstructor
    ~CTank(){
        qDebug()<<"CTank destroyed";
    };
    //!  Seting initial parameters to each tank
    void SetParams(int TankType);
    //! base method responsible for AI move decisions
    void move () override ;
    //! method responsible for player moves
    void move ( int y,int rotation, int turretRotation);
    //! Making new object shell
    void shot();
    //! update state of tank
    void update() override;
     //! Detect if tank is colliding with  other objects
    void Collision_detection(QList <QGraphicsItem*> items) override;
    //! Set type of tank when calling constructor
    void set_TankType(int TankType){ this->TankType=TankType;}
    //! Return type of tank
    int get_TankType(){   return TankType;}
    //! Returns information as to whether the tank is Player or no
    void set_Player(bool player){    this->player=player;}
    bool get_Player() {   return this->player;}
     //! Returns max health of tank
    int get_MaxHealth(){return this->MAX_HEALTH;}
    //! Returns current healt of tank
    int get_CurHealth(){return this->CUR_HEALTH;}
    //! Set current healt of tank
    void set_CurHealth(int health);
    //! Returns current amount of shells, which tank has
    int get_Shells(){return this->ammo;}
    //! Returns current angle of rotated turret of the tank
    qreal get_TurretRotation(){return this->TurretRotation;}
    //! Returns living object of shell
    CShell* get_shell(){ return this->shell;}
    //!Allows to recognize where is  obstacle to avoid
    void collision_mov(double x , double y);
    //! Reset all imposed limits due to current collision state of the tank
    void reset_limitations();
    //! Returns the most important stats of the tank
    QMap<QString, float> getTankStats();
    //! Making move that woould not make any new collision
    void avoid_collision(ICObject* enemy, float dx, float dy);
    //! Setting tank to thewreck
    void set_wreck(bool wreck){this->wreck=wreck;}
    //! Returns if the tank is the wreck
    bool get_wreck(){return wreck;}
    //! Manage all improvs that tank collected
    void manage_improv(CImprovements *improv);
     //! Execute decisions, which were made in move() method
    void decision_maker(int decision, ICObject*object,double dx, double dy);
private:
     //! After Healt of thanks is <0, tank is becoming a wreck
    bool wreck=false;
     //! enemy tank in range_view, which is focused by tank
    CTank *focused_enemy;
     //! Map of imposed limits on the tank
    QMap <int,bool> limitations;
    bool player=false;
    //! Storage of fired shell
    CShell *shell;
    //! Storage of gui representation of fired shell
    CGShell *gshell;
    //! Tank max health
    int MAX_HEALTH;
    //! Tank current health
    int CUR_HEALTH;
     //! Tank type
    int TankType;
     //! Angle of rotation of turret of the tank
    qreal TurretRotation;
    //! Speed of tank's turret rotation
    qreal TurretSpeed;
    //! Speed of fired shell
    qreal Shell_speed;
    //! Armor of tank
    int armor;
    //! Speed of  tank rotation
    float RotationSpeed;
     //! Tank retraction speed
    float reverse_speed;
     //! Ammount of ammo that Tank has
    int ammo;
    //! Reload time
    float reload_time;
     //! Penetration
    int penetration;
    //! Points gained by destroying enemies
    int points;
    //! Time of last fired shot
    int last_shot=0;
     //! Current state of reloading
    int curr_reload=0;
};

#endif // CTANK_H
