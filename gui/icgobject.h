#ifndef ICGOBJECT_H
#define ICGOBJECT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

class ICGObject: public QGraphicsRectItem //! GUI implementation of all objects
{
public:
    ICGObject();
    virtual  ~ICGObject()= default;
    //! Bounding rect of object
    QRectF virtual boundingRect() const=0;
    //! Shape of object
    QPainterPath virtual shape() const=0;
    //! Look of the object
    void virtual paint (QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)=0;
    //! Update state of object in map
    void  virtual advance (int step)=0;
    //! Returns information whether the object should be deleted from the map
    bool get_to_delete(){return this->TO_DELETE;}
    //! Set information whether the object should be deleted from the map
    void set_to_delete(bool del){this->TO_DELETE=del;}
private:
     //! a variable that specifies which objects have to be deleted
    bool TO_DELETE=false;

};


#endif // ICGOBJECT_H
