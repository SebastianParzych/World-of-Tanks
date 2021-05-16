#ifndef ICGOBJECT_H
#define ICGOBJECT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

class ICGObject: public QGraphicsRectItem
{
public:
    ICGObject();
    virtual  ~ICGObject()= default;
    QRectF virtual boundingRect() const=0;
    QPainterPath virtual shape() const=0;
    void virtual paint (QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)=0;
    void  virtual advance (int step)=0;
    bool get_to_delete(){return this->TO_DELETE;}
    void set_to_delete(bool del){this->TO_DELETE=del;}
protected:
     int explosion_time=0;

     bool TO_DELETE=false;
     bool collision_tank=false;
     bool collision_shell=false;
     bool collision_static_object=false;
};

#endif // ICGOBJECT_H
