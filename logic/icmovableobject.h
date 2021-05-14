#ifndef ICMOVABLEOBJECT_H
#define ICMOVABLEOBJECT_H


#include "icobject.h"
#include <cmath>
#include <QtGlobal>



class CMap;

class ICMovableObject: public ICObject
{

public:
    ICMovableObject();
    virtual ~ ICMovableObject()= default;
    virtual void move ()=0;
    virtual void update()=0;
    void set_speed(int speed){this->speed=speed;}
    int get_speed(){return this->speed;}
    void set_RotationXY(float RotationXY){this->RotationXY=RotationXY;}
    qreal get_RotationXY(){return this->RotationXY;}
    void set_Map(CMap *Map){ this->FMap=Map;}
    CMap* get_Map(){ return this->FMap;}
    int get_Range(){return this->view_range;}
    int get_Dmg(){ return this->dmg;}
    void set_Dmg(){this->dmg=dmg;}
protected:
    int dmg;
    int view_range;
    double speed;
    double RotationXY;
    bool islive;
    CMap *FMap;
};

#endif // ICMOVABLEOBJECT_H
