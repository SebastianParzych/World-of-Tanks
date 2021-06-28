#ifndef ICMOVABLEOBJECT_H
#define ICMOVABLEOBJECT_H


#include "icobject.h"
#include <cmath>
#include <QtGlobal>
#include <QGraphicsItem>


class CMap;

class ICMovableObject: public ICObject //! Class of all moving objects in the map - Tank and Shell
{

public:
    //! Constructor of all Movable objects
    ICMovableObject();
    //! Destructor of all Movable objects
    virtual ~ ICMovableObject()= default;
    //! Method responsible for updatting  position of objects
    virtual void move ()=0;
    //! Method responsible for updating state of objects
    virtual void update()=0;
    //! Detection of collisions of objects
    virtual void Collision_detection(QList <QGraphicsItem*> items)=0;
    //! Set speed of object
    void set_speed(int speed){this->speed=speed;}
    //! Returns speed of object
    int get_speed(){return this->speed;}
    //! Set angle of rotation of object
    void set_RotationXY(float RotationXY){this->RotationXY=RotationXY;}
     //! Returns angle of rotation of object
    qreal get_RotationXY(){return this->RotationXY;}
     //! Object recieve information about map (because of that enemy tanks are aware of what is happening in thje map.
    void set_Map(CMap *Map){ this->FMap=Map;}
    //! Object returns map information
    CMap* get_Map(){ return this->FMap;}
    //! Returns damage of tank
    int get_dmg(){ return this->dmg;}
    //! Set damage of tank
    void set_dmg(int dmg){this->dmg=dmg;}
    //! Returns whether the object hit the shell
    bool get_collsion_shell(){ return this->collision_shell;}
    //! Set whether the object hit the shell
    void set_collision_shell(bool set){this->collision_shell=set;}
    //! Returns whether the object hit the tank
    bool get_collsion_tank(){ return this->collision_tank;}
    //!  Set whether the object hit the tank
    void set_collision_tank(bool collision_tank){this->collision_tank=collision_tank;}
    //! Returns view range of object
    int get_View_range(){ return this->view_range;}
    //! Set view range of object
    void set_View_range(int view_range){this->view_range=view_range;}
     //! Set time of explosion
    void set_explosion_time(double explosion_time){this->explosion_time=explosion_time;}
    //! Returns time of explosion
    double get_explosion_time(){return this->explosion_time;}
    //! Returns rotation of object in radians
    void set_angle(double angle){this->angle= angle;}
    //! Set rotation of object in radians
    double get_angle(){return this->angle;}
private:
    //! Rotation of tank in radians
    double angle=0;
    //! After collision with shell explosion_time takes the value of the current time
    double explosion_time=0;
    bool collision_shell=false;
    bool collision_tank=false;
     //! Value of damage dealed by tank and shell
    int dmg;
    //! View range of moving object
    int view_range;
    //! Speed of moving object
    double speed;
    //! Rotation of moving object
    double RotationXY;
     //! Object of map
    CMap *FMap;
};

#endif // ICMOVABLEOBJECT_H
