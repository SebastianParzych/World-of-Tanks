#ifndef CMAP_H
#define CMAP_H

#include "icobject.h"
#include "gui\icgobject.h"
#include <deque>

class CMap //! Class which containing all objects in each layers of application - gui and logic,
           //!Controls the addition and removal of different objects.

{
public:
        //! Constructor of Map
    CMap(int num_of_tanks, int Player_tank,int height, int width);
         //! Deconstructor of Map
    ~CMap(){};
         //! Returns objects whithin a certain range of the object
    std::deque<ICObject*> getObjectInRange(ICObject *obj);
           //! Main method to build static objects in a map
    void BuildStaticObjectMap();
           //! Main method to build all tanks in a map
    void BuildMovableObjectMap();
          //! Deque of all gui objects that are currenlty in map
    std::deque<ICGObject*>getObjToDraw(){return this->FGObjectList; };
           //! Deaue of all objects that are currenlty in map
    std::deque<ICObject*> getObj(){return this->FObjectList;}
        //! Add  new objects to deque, e.g. shell
    void addObj(ICObject *obj){ this->FObjectList.push_front(obj);}
          //! Add new gui object to deque, e.g. cgshell
    void addObjToDraw(ICGObject *obj){this->FGObjectList.push_front(obj);}
          //! Basic alghoritm to create pattern of grass in map
    void set_walls_patern();
          //! Alghoritm to set respawns of tanks and improvements
    void freeSpot(int &pos_X, int &pos_Y);
         //!  Returns width of the map
    int get_Width(){ return this->WIDTH;}
         //! Returns height of the map
    int get_Height(){return this->HEIGHT;}
         //! Method responsible for deleting dead objects
    void ObjHandler();
           //! Methot responsible for setting a player to a specific tank
    void setPlayerToTank();
          //! Set map size
    void setMapSize(int height, int width);
         //! Update state of every object in map
    void update();

private:
        //!  type of player's tank 3- Heavy, 2-Medium,1-Light
    int Player_tank;
         //! type of tank, 3- Heavy, 2-Medium,1-Light
    int TankTypes=3;
        //! Number of all tanks in map
    int num_of_tanks;
    int HEIGHT;
    int WIDTH;
        //!  All objects in map
    std::deque <ICObject*> FObjectList;
        //! All gui objects in map
    std::deque <ICGObject*> FGObjectList;
};

#endif // CMAP_H
