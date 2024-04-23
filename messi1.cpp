#include "messi1.h"
#include"game.h"
#include"player.h"
#include<QPixmap>
#include<QPainter>
#include<QLabel>
//messi1::messi1(QWidget *parent)
  //  : QWidget{parent}
//{}
messi1::messi1(game*g)
{
    g=g;
    this->width=50;
    this->height=80;
    QPainter p(g);
    g->p1.load(QString(":/new/prefix1/image/messi1.png"));
    p.drawPixmap(0,0,100,200,g->p1);
}
