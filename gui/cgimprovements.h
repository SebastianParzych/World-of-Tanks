#ifndef CGIMPROVEMENTS_H
#define CGIMPROVEMENTS_H
#include "logic\cimprovements.h"
#include <QDebug>
#include "icgobject.h"
class CGImprovements: public ICGObject         //! GUI implementation of improvement class
{
public:
    CGImprovements(CImprovements *improv);
    ~ CGImprovements(){
            qDebug()<<"CGImprov deleted";
    };
    //! Update state of object in map
    void advance (int step) override;
    //! Bounding rect of object
    QRectF  boundingRect()const override;
    //! Shape of object
    QPainterPath  shape()const override;
    void set_improv(CImprovements *improv){this->improv=improv;}
    //! Look of the object
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    //! Returns the represented object
    CImprovements* get_improv( ){
        return this->improv;
    }
private:
    QColor color;
    CImprovements *improv;
};

#endif // CGIMPROVEMENTS_H
