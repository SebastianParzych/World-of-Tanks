#ifndef ICOBJECT_H
#define ICOBJECT_H
#include  <QtMath>
#include <deque>
#include <qDebug>
class ICObject //! Class of all objects in the map
{
public:
    //! Constructor of all objects in the  map
    ICObject();
    //! Destructor of all objects in the map
    virtual ~ICObject()= default;
    //! Update state of objects
    virtual void update()=0;
    //! Set position on the map
    void set_pos_xy(int x,int y){
        this->pos_x=x;
        this->pos_y=y;
    }
    //! Returns X coordinate of object
    int get_pos_x(){
        return this->pos_x;
    }
    //! Returns Y coordinate of object
    int get_pos_y(){
        return this->pos_y;
    }
    //! Returns information whether the object should be deleted from the map
    bool get_to_delete(){return this->TO_DELETE;}
    //! Set information whether the object should be deleted from the map
    void set_to_delete(bool del){this->TO_DELETE=del;}
    //! Returns information about visible object-if object is out of view_range player can't seethis object.
    bool get_visible(){return visible;}
    //! Set visible state of object
    void set_visible(bool visible){this->visible=visible;}
    //! Determines the distance between objects
    double get_distance(double x, double y, double dx, double dy){
        return  qSqrt(qPow(pos_x-x+dx,2)+qPow(pos_y-y+dy,2));
    }
     //! Normalize the angle
    qreal normalizeAngle(qreal angle)
    {
        if (angle >= 360)
            angle =0;
        else if (angle <= -360)
            angle= 0;

        return angle;
    }
private:
    //! information about visible state of object
    bool visible=false;
     //! a variable that specifies which objects have to be deleted
    bool TO_DELETE=false;
    //! X coordinate of object
    double  pos_x;
     //! Y coordinate of object
    double  pos_y;
};

#endif // ICOBJECT_H
