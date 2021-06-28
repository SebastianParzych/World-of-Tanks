#ifndef CIMPROVEMENTS_H
#define CIMPROVEMENTS_H

#include "icstaticobject.h"
class CImprovements: public ICStaticObject//! Class of static object -improvements in the map
                                           //!   When a tank enters an object of this class, it gets a random stat boost by some random amount

{
public:
     //! Improvements constructor
    CImprovements();
     //! Improvements deconstructor
    ~CImprovements(){};
    //! Update state of improvement
    void update() override;
    //! Returns Improvement
    float get_upgrade();
    //! Returns the state of improvement (false-Available or true-Used )
    bool get_Open(){return this->opened;}
    //! Set state of improvement (true-Avaible or true-Used)
    void set_Open(bool open){this->opened=open;} \
    //! Returns information about which statistic has to be buffed in tank
    int get_stat(){return this->stat;}
private:
     //! Upgrade value based on quality of improvement
    float upgrade=0;
    bool  opened=false;
    //! Quality of immprovement,the higher the quality, the better the upgrade
    int  quality=0;
    //! Specific statistic ,which is buffed
    int stat=0;
};

#endif // CIMPROVEMENTS_H
