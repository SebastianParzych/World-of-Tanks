 #include "cmap.h"
#include <qDebug>
#include <QtMath>
#include <QRandomGenerator>
#include <memory>
#include <algorithm>
#include "gui\cgtank.h"
#include "gui\cgimprovements.h"
#include "gui\icgobject.h"
CMap::CMap(int num_of_tanks,int Player_tank,int height, int width)
{
    this->HEIGHT=height;
    this->WIDTH=width;
    this->num_of_tanks=num_of_tanks; // how many tanks repsawn
    this->Player_tank=Player_tank;
    BuildMovableObjectMap();
    BuildStaticObjectMap();


}

std::deque<ICObject *> CMap::getObjectInRange(ICObject *main_obj)
{
    std::deque<ICObject*> neighbors;
    for (ICObject* object: FObjectList) {
        if(main_obj == object) continue;
          double x2=qPow(object->getPos_X() - main_obj->getPos_X(),2);
          double y2=qPow(object->getPos_Y()-main_obj->getPos_Y(),2);
          if(qSqrt(x2+y2)<static_cast<ICMovableObject*>(main_obj)->get_Range()+5){
                  object->set_visible(true);
                  neighbors.push_front(object);
          }else{
                object->set_visible(true);
              continue;
          }
      }
    return neighbors;
}

void CMap::freeSpot(int &pos_X, int &pos_Y)
{
    pos_X= QRandomGenerator::global()->bounded(0,HEIGHT);
    pos_Y=QRandomGenerator::global()->bounded(0,WIDTH);
     bool end= false;
     bool unique=false;
     int iter=0;
     int range=250;
     do{
         pos_X= QRandomGenerator::global()->bounded(0,HEIGHT);
         pos_Y=QRandomGenerator::global()->bounded(0,WIDTH);
         if(iter%=10) range-=20;
         if(FObjectList.size()==0)return;
         for (ICObject* object: FObjectList) {
               double x2=qPow(object->getPos_X() - pos_X,2);
               double y2=qPow(object->getPos_Y()-pos_Y,2);
               if(qSqrt(x2+y2)<range){
                  unique=false;
                  break;
               }else unique=true;
           }
         if(unique)end=true;
     }while(!end);
}

void CMap::BuildStaticObjectMap() // statc objects are always being added to the  end of deque
{
    for (int i = 0 ; i <num_of_tanks;i++){
       int pos_X=0, pos_Y=0;
       freeSpot( pos_X,  pos_Y);
       CImprovements *improv= new  CImprovements();
       improv->setPosition(pos_X,pos_Y);
       CGImprovements *gui_improv= new CGImprovements(improv);
       this->FObjectList.push_back(improv);
       this->FGObjectList.push_back(gui_improv);
    }
}
void CMap::BuildMovableObjectMap()
{
    if( this->num_of_tanks<=1)return;
    int tank_type_random;
    for (int i = 0 ; i <num_of_tanks-1;i++){
       int pos_X,pos_Y;
       tank_type_random=QRandomGenerator::global()->bounded(0,3);
       freeSpot(pos_X,pos_Y);
       CTank *tank= new CTank(tank_type_random);
       tank->set_Map(this);
       CGTank *gui_tank= new CGTank (tank);
       tank->setPosition(pos_X,pos_Y);
       this->FObjectList.push_front(tank);
       this->FGObjectList.push_front(gui_tank);
    }

}
void CMap::setPlayerToTank()
{
    int pos_X,pos_Y;
    freeSpot(pos_X,pos_Y);
    CTank *tank= new CTank(Player_tank, true);
    CGTank *gui_tank= new CGTank (tank);
    tank->setPosition(pos_X,pos_Y);
    tank->set_Map(this);
    this->FObjectList.push_front(tank);
    this->FGObjectList.push_front(gui_tank);
}

void CMap::setMapSize(int height, int width)
{
    this->HEIGHT=height;
    this->WIDTH=width;
}

void CMap::update()
{
    for (ICObject* object: FObjectList) {
          object->update();
         if(object->get_to_delete()){
             FObjectList.back();
         }

      }
    for (ICGObject* object: FGObjectList) {

          object->advance(1);
      }
      ObjHandler();
}
void CMap::ObjHandler()
{
    // Deleting dead objects (GUI)
    for(ICGObject*  &pointer : this->FGObjectList)
    {
        if (pointer->get_to_delete())
        {
            delete  pointer;
            pointer = nullptr;
        }
    }
   this->FGObjectList.erase(std::remove(FGObjectList.begin(), FGObjectList.end(), nullptr), FGObjectList.end());
    // Deleting dead objects
    for(ICObject*  &pointer : this->FObjectList)
    {
       if (pointer->get_to_delete())
       {
           delete  pointer;
           pointer = nullptr;
       }
    }
    this->FObjectList.erase(std::remove(FObjectList.begin(), FObjectList.end(), nullptr), FObjectList.end());
}



