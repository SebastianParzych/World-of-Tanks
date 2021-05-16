#ifndef CGIMPROVEMENTS_H
#define CGIMPROVEMENTS_H
#include "logic\cimprovements.h"
#include <QDebug>
#include "icgobject.h"
class CGImprovements: public ICGObject           
{
public:
    CGImprovements(CImprovements *improv);
    ~ CGImprovements(){
            qDebug()<<"CGImprov deleted";
    };
    void advance (int step) override;
    QRectF  boundingRect()const override;
    QPainterPath  shape()const override;
    void set_improv(CImprovements *improv){this->improv=improv;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    CImprovements* get_improv( ){
        return this->improv;
    }
private:
    QColor color;
    CImprovements *improv;
};

#endif // CGIMPROVEMENTS_H
