#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <deque>
#include "cgtank.h"
#include <QPen>
#include <QLineF>

GameWindow::GameWindow(QSize size,int players_num,int tank_type,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
   this->setMinimumSize(size);
   ui->setupUi(this);
   this->players_num=players_num;
   this->setWindowTitle("World of Tanks");
   scene = new QGraphicsScene(this);
   ui->graphicsView->setScene(scene);
   scene->setSceneRect(0, 0, 1500, 900);
   ui->graphicsView->setRenderHint(QPainter::Antialiasing);
   scene->setItemIndexMethod(QGraphicsScene::NoIndex);
   ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
   ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
   ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
   game= new CGame(players_num,tank_type,1600,800);
   SetObjects(game->GetMap());
   timer = new QTimer(this);
   connect(timer, &QTimer::timeout, this, &GameWindow::update_game); // checking all important keys
   timer->setInterval(1000 / 33);
   timer->start();

}
GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::AddObjects(){
    if((game->GetMap()->getObjToDraw()).size()>this->map_elements){
        scene->addItem(game->GetMap()->getObjToDraw().front());
        this->map_elements=game->GetMap()->getObjToDraw().size();
    }
}

void GameWindow::SetObjects(CMap *map)
{
    this->map_elements=(map->getObjToDraw()).size();
    qDebug()<<map_elements;
    for (ICGObject* object: map->getObjToDraw()) {
          scene->addItem(object);
          if( dynamic_cast<CGTank*>(object)->get_Player()){
              player=static_cast<CGTank*>(object)->getTank();
              ui->Health->setRange(0,player->get_MaxHealth());
              ui->Shells->setRange(0,player->get_Shells());
          }
    }
}

void GameWindow::UpdateStats()
{
        ui->Health->setValue(player->get_CurHealth());
        ui->Shells->setValue(player->get_Shells());
}

void GameWindow::keyPressEvent(QKeyEvent *event){
     keys[event->key()] = true;
}

void GameWindow::keyReleaseEvent(QKeyEvent *e)
{
    keys[e->key()] = false;
}
void GameWindow::update_game() // Map of all functional keys
{
       UpdateStats();
       AddObjects();
       if(keys[Qt::Key_A])
       {
           player->move(0,-1,0);
       }
       if(keys[Qt::Key_D])
       {
             player->move(0,1,0);
       }
       if(keys[Qt::Key_S])
       {
           player->move(1,0,0);
       }
       if(keys[Qt::Key_W])
       {
           player->move(-1,0,0);
       }
       if(keys[Qt::Key_J])
       {
           player->move(0,0,-1);
       }
       if(keys[Qt::Key_L])
       {
          player->move(0,0,1);
       }
       if(keys[Qt::Key_Space])
       {
         player->shot();
       }
       if(keys[Qt::Key_Escape]){
            qApp->exit();
       }
}

