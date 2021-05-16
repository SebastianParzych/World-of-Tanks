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

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QSize size,int players_num,int tank_type,QWidget *parent = nullptr);
    ~GameWindow();
    void SetObjects(CMap *map);
    void AddObjects();

private:
    bool set =false;
    int tank_type=0;
    bool current_window=false;
    QTimer *timer;
    QMap<int, bool> keys;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *e);
    int map_elements;
    int players_num;
    CGame *game;
    CTank *player;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsRectItem *rec;
    Ui::GameWindow *ui;
private slots:
    void update_game();
    void UpdateStats();

};

#endif // GAMEWINDOW_H
