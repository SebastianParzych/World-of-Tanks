#ifndef CGAME_H
#define CGAME_H

#include <QTimer>
#include "cmap.h"
#include "gui\icgobject.h"
#include <QKeyEvent>
class CGame: public QObject
{
       Q_OBJECT
public:
    CGame(int player_num, int TankType,int height, int width);
    ~CGame(){};
    CMap* GetMap(){return map;}
public slots:
    void step();
private:
    int width;
    int height;
    QTimer timer;
    bool state_of_game=false;
    int NUM_PLAYERS;
    const float DELTA_T=0.001;
    CMap *map;

};

#endif // CGAME_H
