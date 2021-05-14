#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QApplication>
#include "cgtank.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->light->setBackgroundBrush(Qt::gray);
    ui->medium->setBackgroundBrush(Qt::gray);
    ui->heavy->setBackgroundBrush(Qt::gray);
    CGTank *t_light = new CGTank(2);
    CGTank *t_medium = new CGTank(1);
    CGTank *t_heavy = new CGTank(0);
    display_tanks(t_light,ui->ligh_t,ui->light);
    display_tanks(t_medium,ui->medium_t,ui->medium);
    display_tanks(t_heavy,ui->heavy_t,ui->heavy);
    this->setWindowTitle("World of Tanks        MENU");

}

MainWindow::~MainWindow()
{
    delete  ui->light->scene();
    delete  ui->medium->scene();
    delete  ui->heavy->scene();
    if(gamewindow!=nullptr) {
       delete gamewindow;
    }
    delete ui;

}

void MainWindow::display_tanks(CGTank *tank,QTableWidget *table,QGraphicsView *t_view)
{
    QGraphicsScene *scene=new QGraphicsScene();
    t_view->setScene(scene);
    scene->setSceneRect(-85, -85,200, 200);
    scene->addItem(tank);
    QMap <QString,float> stats = tank->getTank()->getTankStats();
    QMap <QString,float>::iterator it=stats.begin(); // iterate through map to fill table

    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setRowCount(stats.size());
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"Stat name","value"});
    for ( int i =0; i<table->rowCount();i++){
        QTableWidgetItem *item;
        for(int j =0; j<table->columnCount();j++){
            item= new QTableWidgetItem;
            if(j==0){
                item->setText(it.key());
            }
            if( j==1){
                item->setText(QString::number(it.value()));
            }
            table->setItem(i,j,item);
        }

       if(it !=stats.end()){
           it++;
       }
    }
}
void MainWindow::on_Play_clicked(){  ui->stackedWidget->setCurrentIndex(1);}

void MainWindow::on_Settings_clicked(){ ui->stackedWidget->setCurrentIndex(2);}

void MainWindow::on_back_op_clicked(){   ui->stackedWidget->setCurrentIndex(0);}

void MainWindow::on_back_play_clicked(){  ui->stackedWidget->setCurrentIndex(0);}

void MainWindow::on_Light_tank_toggled(bool checked){
    if(checked){
        tank_choice=2;
        ui->light->setBackgroundBrush(QBrush(QColor(255, 159, 0), Qt::SolidPattern));
        ui->medium->setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));
        ui->heavy->setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));
        ui->Medium_tank->setChecked(false);
        ui->Heavy_tank->setChecked(false);
        }
    }
void MainWindow::on_Medium_tank_toggled(bool checked){
    if(checked){
        tank_choice=1;
        ui->light->setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));
        ui->medium->setBackgroundBrush(QBrush(QColor(255, 159, 0), Qt::SolidPattern));
        ui->heavy->setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));

        }      ui->Light_tank->setChecked(false);
    ui->Heavy_tank->setChecked(false);
    }
void MainWindow::on_Heavy_tank_toggled(bool checked){
    if(checked){
        tank_choice=0;
        ui->light->setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));
        ui->medium->setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));
        ui->heavy->setBackgroundBrush(QBrush(QColor(255, 159, 0), Qt::SolidPattern));
        ui->Medium_tank->setChecked(false);
        ui->Light_tank->setChecked(false);
        }
    }

void MainWindow::on_Quit_clicked()
{
    qApp->exit();
}

void MainWindow::on_start_game_clicked()
{
    hide();
    int players_num=2;
    players_num=ui->slide_players_num->value();
    QSize size = this->size();
    gamewindow= new GameWindow(size,players_num,tank_choice);
    //gamewindow->setModal(true);
    //gamewindow->exec();
    gamewindow->show();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Reset_clicked()
{
    ui->slide_players_num->setValue(1);
    ui->slide_dif->setValue(1);

}





