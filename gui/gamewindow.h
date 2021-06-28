#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCore>
#include <QGraphicsScene>
#include <QTimer>
#include <QtGui>
#include "logic\cmap.h"
#include "logic\ctank.h"
#include "logic\cgame.h"
#include <QKeyEvent>
namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow  //!The class that displays the entire game, receives keyboard signals and sends them to the tank controlled by player
{
    Q_OBJECT

public:
    explicit GameWindow(QSize size,int players_num,int tank_type,QWidget *parent = nullptr); //! Constructor of game window
    ~GameWindow();
    //! Adding all objects to the scene
    void SetObjects(CMap *map);
     //! Adding new objects to the scene
    void AddObjects();

private:
    //! Variable which inform if initial objects have been added to the scene
    bool set =false;
    //! Choosed by player tank type
    int tank_type=0;
    bool current_window=false;
    //! Timer that fires up KeyPresseEvents
    QTimer *timer;
    //! Map of all key bindings used to play game
    QMap<int, bool> keys;
    //! Recieve Key press events
    void keyPressEvent(QKeyEvent *event);
     //! Recieve Key release enents
    void keyReleaseEvent(QKeyEvent *e);
    //! Number of all elemetns in scene
    int map_elements;
    //! Number of all tanks in sceene
    int players_num;
    //! Object of game that stores all game related objects
    CGame *game;
    //! Object of player's tank
    CTank *player;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsRectItem *rec;
    Ui::GameWindow *ui;
private slots:
    //! Update scene every time timer fires up
    void update_game();
     //! Update stats every time timer fires up
    void UpdateStats();

};

#endif // GAMEWINDOW_H
