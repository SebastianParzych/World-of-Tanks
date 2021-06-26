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
    void setPosition(int x,int y){
        this->pos_x=x;
        this->pos_y=y;
    }
    int getPos_X(){
        return this->pos_x;
    }
    int getPos_Y(){
        return this->pos_y;
    }
    bool get_to_delete(){return this->TO_DELETE;}
    void set_to_delete(bool del){this->TO_DELETE=del;}
    bool get_visible(){return visible;}
    void set_visible(bool visible){this->visible=visible;}
    double get_distance(double x, double y, double dx, double dy){
        return  qSqrt(qPow(pos_x-x+dx,2)+qPow(pos_y-y+dy,2));
    }
    double get_height(){return height;}
    double get_width(){return width;}
    qreal get_angle(){return angle;}
    qreal normalizeAngle(qreal angle)
    {
        if (angle >= 360)
            angle =0;
        else if (angle <= -360)
            angle= 0;

        return angle;
    }
    void map_corners(){
         top_left.x = pos_x - ((width / 2) * cos(angle)) - ((height / 2) * sin(angle));
         top_left.y = pos_y - ((width / 2) * sin(angle)) + ((height / 2) * cos(angle));
         top_right.x = pos_x - ((width / 2) * cos(angle)) + ((height / 2) * sin(angle));
         top_right.y = pos_y - ((width / 2) * sin(angle)) - ((height / 2) * cos(angle));
         bot_left.x = pos_x + ((width / 2) * qCos(angle)) - ((height / 2) * qSin(angle));
         bot_left.y = pos_y + ((width / 2) * sin(angle)) + ((height / 2) * cos(angle));
         bot_right.x = pos_x + ((width / 2) * cos(angle)) + ((height / 2) * sin(angle));
         bot_right.y = pos_y + ((width / 2) * sin(angle)) - ((height / 2) * cos(angle));
    }

    std::deque<double> get_corners_x()
    {
        std::deque<double> x_coords {top_left.x,top_right.x,bot_left.x,bot_right.x};
        return x_coords;
    }
    std::deque<double> get_corners_y()
    {
        std::deque<double> y_coords {top_left.y,top_right.y,bot_left.y,bot_right.y};
        return y_coords;
    }

protected:
    double height;
    double width;
    qreal angle;
    bool visible=false;
    bool TO_DELETE=false;
    double  pos_x;
    double  pos_y;
    struct Corner_point {
        double x;
        double y;
    };
    struct Corner_point top_left;
    struct Corner_point top_right;
    struct Corner_point bot_left;
    struct Corner_point bot_right;
};

#endif // ICOBJECT_H
