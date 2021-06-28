#ifndef ICSTATICOBJECT_H
#define ICSTATICOBJECT_H

#include "icobject.h"

class ICStaticObject: public ICObject //! Class of all static objects in the map
{
public:
    //! Construcot of static objects
    ICStaticObject();
    //! Deconstrucot of static objects
    virtual ~ ICStaticObject()= default;
    //! Update state of static objects
    virtual void update ()=0;

};

#endif // ICSTATICOBJECT_H
