#ifndef CGRASS_H
#define CGRASS_H


#include "icstaticobject.h"

class CGrass: public ICStaticObject //! Class of static object -grass in the map
{
public:
    //! Grass constructor
    CGrass();
    //! Grass deconstructor
    ~CGrass(){};
     //! Update state of grass
    void update() override;
};

#endif // CGRASS_H
