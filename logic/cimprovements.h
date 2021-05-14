#ifndef CIMPROVEMENTS_H
#define CIMPROVEMENTS_H

#include "icstaticobject.h"

class CImprovements: public ICStaticObject
{
public:
    CImprovements();
    ~CImprovements(){};

    void update() override;

private:
    float Ratio;
    float Scale;
};

#endif // CIMPROVEMENTS_H
