#ifndef CGSHELL_H
#define CGSHELL_H

#include "icgobject.h"
#include "logic\cshell.h"
class CGShell : public ICGObject
{
public:
    CGShell(CShell *shell);
    ~CGShell(){
        qDebug()<<"CGShell deleted";
    };
    void advance (int step)override;
    QRectF boundingRect()  const override;
    QPainterPath shape()  const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    CShell* get_Shell(){return this->shell;}
private:
    int last_x;
    int last_y;
    CShell *shell;
    qreal Direction=0;
    qreal speed=5;
    QColor color;
};

#endif // CGSHELL_H
