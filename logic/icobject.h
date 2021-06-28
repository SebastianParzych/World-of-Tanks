#ifndef ICOBJECT_H
#define ICOBJECT_H
#include  <QtMath>
#include <deque>
#include <qDebug>
class ICObject
{
public:
    ICObject();
    virtual ~ICObject()= default;
    virtual void update()=0;
    void set_pos_xy(int x,int y){
        this->pos_x=x;
        this->pos_y=y;
    }
    int get_pos_x(){
        return this->pos_x;
    }
    int get_pos_y(){
        return this->pos_y;
    }
    void set_angle(qreal angle){ this->angle=angle;}
    qreal get_angle(){return angle;}
    bool get_to_delete(){return this->TO_DELETE;}
    void set_to_delete(bool del){this->TO_DELETE=del;}
    bool get_visible(){return visible;}
    void set_visible(bool visible){this->visible=visible;}
    double get_distance(double x, double y, double dx, double dy){
        return  qSqrt(qPow(pos_x-x+dx,2)+qPow(pos_y-y+dy,2));
    }

    qreal normalizeAngle(qreal angle)
    {
        if (angle >= 360)
            angle =0;
        else if (angle <= -360)
            angle= 0;

        return angle;
    }
private:
    qreal angle;
    bool visible=false;
    bool TO_DELETE=false;
    double  pos_x;
    double  pos_y;
};

#endif // ICOBJECT_H
