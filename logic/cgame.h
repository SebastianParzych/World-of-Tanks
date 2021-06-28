#ifndef CGAME_H
#define CGAME_H

#include <QTimer>
#include "cmap.h"
#include "gui\icgobject.h"
#include <QKeyEvent>
class CGame: public QObject //! CLass which controlls Objects updates in the map
{
       Q_OBJECT
public:
    //! Game constructor
    CGame(int player_num, int TankType,int height, int width);
    //! Game deconstructor
    ~CGame(){};
    //! Returns Map object
    CMap* GetMap(){return map;}
public slots:
     //! Method which update all objects in map
    void step();
private:
    //! Map width
    int width;
    //! Map height
    int height;
    //! Timer that fires up step method
    QTimer timer;
    //! State of game, if true game is ending
    bool state_of_game=false;
    //! Number of players
    int NUM_PLAYERS;
    //! Timer intervals
    const float DELTA_T=0.001;
    //! Map object
    CMap *map;

};

#endif // CGAME_H
