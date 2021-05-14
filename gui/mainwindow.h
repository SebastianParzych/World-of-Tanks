#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <gui\gamewindow.h>
#include "logic\cgame.h"
#include "logic\cmap.h"
#include<gui\cgtank.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display_tanks(CGTank *tank,QTableWidget *table,QGraphicsView *t_view);
private slots:
    void on_Play_clicked();
    void on_Settings_clicked();
    void on_Quit_clicked();
    void on_start_game_clicked();
    void on_back_op_clicked();
    void on_back_play_clicked();
    void on_Reset_clicked();
    void on_Light_tank_toggled(bool checked);
    void on_Medium_tank_toggled(bool checked);
    void on_Heavy_tank_toggled(bool checked);

private:
    int tank_choice=0;
    GameWindow *gamewindow=nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
