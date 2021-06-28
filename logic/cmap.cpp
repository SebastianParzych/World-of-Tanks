 #include "cmap.h"
#include <qDebug>
#include <QtMath>
#include <QRandomGenerator>
#include <memory>
#include <algorithm>
#include "gui\cgtank.h"
#include "gui\cgimprovements.h"
#include "gui\icgobject.h"
#include "gui\cgwall.h"
#include "cwall.h"
CMap::CMap(int num_of_tanks,int Player_tank,int height, int width)
{
    this->HEIGHT=height;
    this->WIDTH=width;
    this->num_of_tanks=num_of_tanks; // how many tanks repsawn
    this->Player_tank=Player_tank;
    BuildStaticObjectMap();
    BuildMovableObjectMap();
}

std::deque<ICObject *> CMap::getObjectInRange(ICObject *main_obj)
{
    std::deque<ICObject*> neighbors;
    for (ICObject* object: FObjectList) {
        if(main_obj == object) continue;
          double x2=qPow(object->get_pos_x() - main_obj->get_pos_y(),2);
          double y2=qPow(object->get_pos_x()-main_obj->get_pos_y(),2);
          if(qSqrt(x2+y2)<static_cast<ICMovableObject*>(main_obj)->get_range()+5){
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
         if(iter%10==0) range-=25;
         if(FObjectList.size()==0)return;
         for (ICObject* object: FObjectList) {
               double x2=qPow(object->get_pos_x() - pos_X,2);
               double y2=qPow(object->get_pos_y()-pos_Y,2);
               if(qSqrt(x2+y2)<range){
                  unique=false;
                  break;
               }else unique=true;
           }
         if(unique)end=true;
     }while(!end);
}
void CMap::set_walls_patern() // 1 - 30x 30;
{
 int block_chain=QRandomGenerator::global()->bounded(10,50);
 int pos_x = QRandomGenerator::global()->bounded(0,HEIGHT);
 int pos_y = QRandomGenerator::global()->bounded(0,WIDTH);
 int factor=0;
 do{
     factor=QRandomGenerator::global()->bounded(-1,2);
     if(factor == 1 or factor == -1 ){
      break;
     }
 }while(true);
 freeSpot( pos_x, pos_y);
 for( int i =0 ; i<block_chain/2; i++){
     CWall *wall_1= new CWall ();
     CWall *wall_2= new CWall ();
     wall_1->set_pos_xy(pos_x,pos_y+factor*i*30);
     CGWall *gui_wall_1= new CGWall(wall_1);
     this->FObjectList.push_back(wall_1);
     this->FGObjectList.push_back(gui_wall_1);

     wall_2->set_pos_xy(pos_x+factor*i*30,pos_y);
     CGWall *gui_wall_2= new CGWall(wall_2);
     this->FObjectList.push_back(wall_2);
     this->FGObjectList.push_back(gui_wall_2);
 }
}
void CMap::BuildStaticObjectMap() // statc objects are always being added to the  end of deque
{
    for (int i = 0 ; i <5;i++){
        set_walls_patern();
    }
    for (int i = 0 ; i <num_of_tanks;i++){
       int pos_X=0, pos_Y=0;
       freeSpot( pos_X,  pos_Y);
       CImprovements *improv= new  CImprovements();
       improv->set_pos_xy(pos_X,pos_Y);
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
       tank->set_pos_xy(pos_X,pos_Y);
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
    tank->set_pos_xy(pos_X,pos_Y);
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



