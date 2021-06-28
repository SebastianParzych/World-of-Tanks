#ifndef ICMOVABLEOBJECT_H
#define ICMOVABLEOBJECT_H


#include "icobject.h"
#include <cmath>
#include <QtGlobal>
#include <QGraphicsItem>


class CMap;

class ICMovableObject: public ICObject
{

public:
    ICMovableObject();
    virtual ~ ICMovableObject()= default;
    virtual void move ()=0;
    virtual void update()=0;
    virtual void Collision_detection(QList <QGraphicsItem*> items)=0;
    void set_speed(int speed){this->speed=speed;}
    int get_speed(){return this->speed;}
    void set_RotationXY(float RotationXY){this->RotationXY=RotationXY;}
    qreal get_RotationXY(){return this->RotationXY;}
    void set_Map(CMap *Map){ this->FMap=Map;}
    CMap* get_Map(){ return this->FMap;}
    int get_range(){return this->view_range;}
    int get_dmg(){ return this->dmg;}
    void set_dmg(int dmg){this->dmg=dmg;}
    bool get_collsion_shell(){ return this->collision_shell;}
    void set_collision_shell(bool set){this->collision_shell=set;}
    bool get_collsion_tank(){ return this->collision_tank;}
    void set_collision_tank(bool collision_tank){this->collision_tank=collision_tank;}
    int get_View_range(){ return this->view_range;}
    void set_View_range(int view_range){this->view_range=view_range;}
private:
    bool collision_shell=false;
    bool collision_tank=false;
    int dmg;
    int view_range;
    double speed;
    double RotationXY;
    bool islive;
    CMap *FMap;
};

#endif // ICMOVABLEOBJECT_H
