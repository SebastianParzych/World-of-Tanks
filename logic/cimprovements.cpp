#include "cimprovements.h"
#include <QRandomGenerator>
CImprovements::CImprovements() : ICStaticObject(){
    width =20;
    height= 30;
    angle=0;
    map_corners();
    stat=QRandomGenerator::global()->bounded(0,9);
    quality=QRandomGenerator::global()->bounded(0,10);

}

void CImprovements::update()
{
    return;
}

float CImprovements::get_upgrade()
{
    this->set_Open(true);
    upgrade=1.05+ 0.05*quality;
    return upgrade;
}
