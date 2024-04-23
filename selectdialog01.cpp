#include "selectdialog01.h"
#include "playerbutton.h"
#include<QPaintEvent>
#include<QPainter>
selectdialog01::selectdialog01(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(1050,600);
    this->setWindowTitle("SoccerGoal");
    this->setWindowIcon(QIcon(":/new/prefix1/image/soccersecond.jpg"));
    messi=new playerbutton(":/new/prefix1/image/messi.jpg");
    messi->setParent(this);
    messi->move(50,50);
    messi->setFixedSize(150,200);
    ronaldo=new playerbutton(":/new/prefix1/image/ronaldo.jpg");
    ronaldo->setParent(this);
    ronaldo->move(250,50);
    ronaldo->setFixedSize(150,200);
    neymar=new playerbutton(":/new/prefix1/image/neymar.jpg");
    neymar->setParent(this);
    neymar->move(450,50);
    neymar->setFixedSize(150,200);
    mbappe=new playerbutton(":/new/prefix1/image/mbappe.jpg");
    mbappe->setParent(this);
    mbappe->move(650,50);
    mbappe->setFixedSize(150,200);
    modric=new playerbutton(":/new/prefix1/image/modric.jpg");
    modric->setParent(this);
    modric->move(850,50);
    modric->setFixedSize(150,200);
    virgil=new playerbutton(":/new/prefix1/image/virgil.jpg");
    virgil->setParent(this);
    virgil->move(50,300);
    virgil->setFixedSize(150,200);
    lukaku=new playerbutton(":/new/prefix1/image/lukaku.jpg");
    lukaku->setParent(this);
    lukaku->move(250,300);
    lukaku->setFixedSize(150,200);
    bale=new playerbutton(":/new/prefix1/image/bale.jpg");
    bale->setParent(this);
    bale->move(450,300);
    bale->setFixedSize(150,200);
    muller=new playerbutton(":/new/prefix1/image/muller.jpg");
    muller->setParent(this);
    muller->move(650,300);
    muller->setFixedSize(150,200);
    son=new playerbutton(":/new/prefix1/image/son.jpg");
    son->setParent(this);
    son->move(850,300);
    son->setFixedSize(150,200);
}
void selectdialog01::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap selbackground;
    selbackground.load(":/new/prefix1/image/chooseplayer.png");
    painter.drawPixmap(0,0,this->width(),this->height(),selbackground);
}
