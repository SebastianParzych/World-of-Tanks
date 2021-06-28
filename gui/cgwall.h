#ifndef CGWALL_H
#define CGWALL_H

#include "icgobject.h"
#include "logic/cwall.h"

class CGWall: public ICGObject
{
public:
public:
    CGWall(CWall *wall);
    ~ CGWall(){
            qDebug()<<"CGImprov deleted";
    };
    void advance (int step) override;
    QRectF  boundingRect()const override;
    QPainterPath  shape()const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
private:
    QColor color;
    CWall *wall;
};

#endif // CGWALL_H
