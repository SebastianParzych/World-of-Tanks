#ifndef CGGRASS_H
#define CGGRASS_H

#include "icgobject.h"
#include "logic/cgrass.h"

class CGGrass: public ICGObject //! GUI implementation of grass class
{
public:
public:
    CGGrass(CGrass *grass);
    ~ CGGrass(){
            qDebug()<<"CGImprov deleted";
    };
    //! Update state of object in map
    void advance (int step) override;
    //! Bounding rect of object
    QRectF  boundingRect()const override;
    //! Shape of object
    QPainterPath  shape()const override;
    //! Look of the object
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
private:
    QColor color;
    CGrass *grass;
};

#endif // CGGRASS_H
