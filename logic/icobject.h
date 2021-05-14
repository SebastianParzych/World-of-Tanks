#ifndef ICOBJECT_H
#define ICOBJECT_H
#include  <QtMath>

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
protected:
    bool visible=false;
    bool TO_DELETE=false;
    double  pos_x;
    double  pos_y;
};

#endif // ICOBJECT_H
