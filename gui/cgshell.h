#ifndef CGSHELL_H
#define CGSHELL_H

#include "icgobject.h"
#include "logic\cshell.h"
class CGShell : public ICGObject //! GUI implementation of grass shell
{
public:
    CGShell(CShell *shell);
    ~CGShell(){
        qDebug()<<"CGShell deleted";
    };
    //! Update state of object in map
    void advance (int step)override;
    //! Bounding rect of object
    QRectF boundingRect()  const override;
    //! Shape of object
    QPainterPath shape()  const override;
    //! Look of the object
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    //!Returns the represented  theo object
    CShell* get_Shell(){return this->shell;}
private:
     //! Last X coordinate of the object
    int last_x;
    //! Last Y coordinate of the object
    int last_y;
    //! Base object, whtich gui class is representing
    CShell *shell;
     //! Direction of fly of shell
    qreal Direction=0;
     //! Speed of shell (Base value )
    qreal speed=5;
    QColor color;
};

#endif // CGSHELL_H
