#ifndef CWALL_H
#define CWALL_H


#include "icstaticobject.h"

class CWall: public ICStaticObject
{
public:
    CWall();
    ~CWall(){};
    void update() override;
};

#endif // CWALL_H
