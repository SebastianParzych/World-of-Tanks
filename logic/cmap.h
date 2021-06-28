#ifndef CMAP_H
#define CMAP_H

#include "icobject.h"
#include "gui\icgobject.h"
#include <deque>

class CMap
{
public:
    CMap(int num_of_tanks, int Player_tank,int height, int width);
    ~CMap(){};
    std::deque<ICObject*> getObjectInRange(ICObject *obj);
    void BuildStaticObjectMap();
    void BuildMovableObjectMap();
    std::deque<ICGObject*>getObjToDraw(){return this->FGObjectList; };
    std::deque<ICObject*> getObj(){return this->FObjectList;}
    void addObj(ICObject *obj){ this->FObjectList.push_front(obj);}
    void addObjToDraw(ICGObject *obj){this->FGObjectList.push_front(obj);}
    void set_walls_patern();
    void freeSpot(int &pos_X, int &pos_Y);
    int get_Width(){ return this->WIDTH;}
    int get_Height(){return this->HEIGHT;}
    void ObjHandler();
    void setPlayerToTank();
    void setMapSize(int height, int width);
    void update();
private:
    int Player_tank;
    int TankTypes=3;
    int num_of_tanks;
    int HEIGHT;
    int WIDTH;
    std::deque <ICObject*> FObjectList;
    std::deque <ICGObject*> FGObjectList;
};

#endif // CMAP_H
