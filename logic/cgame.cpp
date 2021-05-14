#include "cgame.h"
#include "icobject.h"
#include "gui\icgobject.h"
#include <QDebug>
CGame::CGame(int player_num,int TankType, int height, int width)  {
        this->NUM_PLAYERS=player_num;
        map= new CMap(this->NUM_PLAYERS, TankType,height,width);
        map->setPlayerToTank();


        QObject::connect(&timer, &QTimer::timeout, this,&CGame::step);
        timer.start(1000 / 33);
}



void CGame::step(){
    map->update();
}


