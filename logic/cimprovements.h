#ifndef CIMPROVEMENTS_H
#define CIMPROVEMENTS_H

#include "icstaticobject.h"
class CImprovements: public ICStaticObject
{
public:
    CImprovements();
    ~CImprovements(){};
    void update() override;
    float get_upgrade();
    bool get_Open(){return this->opened;}
    void set_Open(bool open){this->opened=open;}
    int get_stat(){return this->stat;}
private:
    float upgrade=0;
    bool  opened=false;
    int  quality=0;
    int stat=0;
};

#endif // CIMPROVEMENTS_H
