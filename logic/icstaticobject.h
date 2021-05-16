#ifndef ICSTATICOBJECT_H
#define ICSTATICOBJECT_H

#include "icobject.h"

class ICStaticObject: public ICObject
{
public:
    ICStaticObject();
    virtual ~ ICStaticObject()= default;
    virtual void update ()=0;

};

#endif // ICSTATICOBJECT_H
