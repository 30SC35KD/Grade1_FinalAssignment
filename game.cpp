#include "game.h"
#include<QPaintEvent>
#include<QPainter>
#include<QPixmap>
#include"selectdialog1.h"
#include<QObject>
#include"player.h"
#include<QLabel>
#include<qdebug.h>
#include"playerbutton.h"
#include"player.h"
#include"ball.h"
#include<QRandomGenerator>
game::game(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(1500,900);
    setWindowIcon(QIcon(":/new/prefix1/image/soccer (1).jpg"));
    keyRespondTimer = new QTimer(this);	//构造函数中创建定时器对象，并连接信号槽
    connect(keyRespondTimer, &QTimer::timeout, this, &game::slotTimeOut);
    QPushButton *button=new QPushButton(this);
    connect(button, &QPushButton::clicked,[=]{this->startTimer(5);});

}
void game::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QPixmap gameground;
    gameground.load(":/new/prefix1/image/court.jpg");
    p.drawPixmap(0,0,this->width(),this->height(),gameground);
    p.setPen(Qt::black);
    p.drawPixmap(b->x,b->y,2*b->r,2*b->r,QPixmap(":/new/prefix1/image/ball.png"));

}
void game::timerEvent(QTimerEvent *event)
{   if(b->y==690&&b->vx!=0)
        b->f=0.01;
    else
        b->f=0;
    if(b->x<=180)
    {b->x=180;
        b->vx=-(b->vx/2);
        b->vy=-(b->vy/2);
    }
    if(b->x+2*b->r>=1320)
    {b->x=1320-2*b->r;
        b->vx=-(b->vx/2);
        b->vy=-(b->vy/2);
    }

    if(b->vx>0)
    {
        b->vx-=b->f;
        if(b->vx<=0)
            b->vx=0;
    }
    else if(b->vx<0)
    {
        b->vx+=b->f;
        if(b->vx>=0)
            b->vx=0;
    }

    b->x+=b->vx;
    b->y+=b->vy;
    b->vy+=b->g;
    if(b->y>690&&abs(b->vy)<=0.5)
    {b->vy=0;b->g=0;b->y=690;}
    else
        b->g=0.1;
    if(b->y>690&&abs(b->vy)>0.5)
    {b->y=690;
        b->vy=-(b->vy/2.0);
    }
    p1->move(p1->x(),p1->y()-p1->jumpspeed);
    p1->jumpspeed-=p1->gravity;
    if(p1->y()+p1->height>=750)
    {
        p1->move(p1->x(),750-p1->height);
        p1->jumpspeed=0;
        p1->gravity=0;
    }
    p2->move(p2->x(),p2->y()-p2->jumpspeed);
    p2->jumpspeed-=p2->gravity;
    if(p2->y()+p2->height>=750)
    {
        p2->move(p2->x(),750-p2->height);
        p2->jumpspeed=0;
        p2->gravity=0;
    }
    this->header();
    this->update();
}
void game::keyPressEvent(QKeyEvent *k){

    if(!k->isAutoRepeat())  //判断如果不是长按时自动触发的按下,就将key值加入容器
        keys.append(k->key());
    if(!keyRespondTimer->isActive()) //如果定时器不在运行，就启动一下
        keyRespondTimer->start(6);
    if(k->key()==Qt::Key_W)
    {
        if(p1->y()==750-p1->height)
        {
            p1->jumpspeed=p1->v_jump;
            p1->gravity=0.3;
        }
    }
        if(k->key()==Qt::Key_5)
        {
            if(p2->y()==750-p2->height)
            {
                p2->jumpspeed=p2->v_jump;
                p2->gravity=0.3;
            }
    }
    if(k->key()==Qt::Key_S)
    {if((b->x-(p1->x()+p1->width()))<50&&(b->x-p1->x()>0.8*p1->width())&&(b->y>=p1->y()+0.3*p1->height)&&(b->y<=p1->y()+p1->height))
        {if(b->vx<=-10)
                b->vx=0;
            else
                b->vx+=10;
            b->vy-=(12-12*((b->x-(p1->x()+0.8*p1->width()))/(0.2*p1->width()+50)));
        }

    }
if(k->key()==Qt::Key_2)
    {
        if(p2->x()-(b->x+2*b->r)<=50&&p2->x()+p2->width()-(b->x+2*b->r)>=0.8*p2->width()&&b->y>=p2->y()+0.3*p2->height&&b->y<=p2->y()+p2->height)
        {
        if(b->vx>=10)
            b->vx=0;
        else
            b->vx-=10;
        b->vy-=(12-12*((p2->x()+0.2*p2->width()-(b->x+2*b->r))/(0.2*p2->width()+50)));
        }

}

    }

void game::keyReleaseEvent(QKeyEvent *k){
    if(!k->isAutoRepeat())  //判断如果不是长按时自动触发的释放,就将key值从容器中删除
        keys.removeAll(k->key());
    if(keys.isEmpty()) //容器空了，关闭定时器
        keyRespondTimer->stop();
if(k->key()==Qt::Key_A)
    { p1->v_run=0;}
if(k->key()==Qt::Key_D)
    p1->v_run=0;
if(k->key()==Qt::Key_1)
    p2->v_run=0;
if(k->key()==Qt::Key_3)
    p1->v_run=0;

}

void game::slotTimeOut()
{
    foreach (int key, keys)
    {
        if(key==Qt::Key_A)
        {p1->move(p1->x()-p1->v, p1->y());
            if(p1->x()<=185-p1->weight)
                p1->move(185-p1->weight,p1->y());
            p1->v_run=-p1->v;
        }
        if(key==Qt::Key_D)
        {p1->move(p1->x()+p1->v, p1->y());
            if(p1->x()>=1325-p1->weight)
                p1->move(1325-p1->weight,p1->y());
            p1->v_run=p1->v;
        }

        if(key==Qt::Key_3)
        {
            p2->move(p2->x()+p2->v,p2->y());
            if(p2->x()>=1315)
                p2->move(1315,p2->y());
            p2->v_run=p2->v;
        }
        if(key==Qt::Key_1)
        {  p2->move(p2->x()-p2->v, p2->y());
            if(p2->x()<=175)
                p2->move(175,p2->y());
            p2->v_run=-p2->v;
        }
    }

}
void game::dribble()
{int m=QRandomGenerator::global()->bounded(2);
    if(m==0)
        b->x=p2->right;
    else if(m==1)
      b->x=p1->left-2*b->r;
}
void game::header()
{p1->left=p1->x()+0.2*p1->width();
    p1->right=p1->x()+0.8*p1->width();
    p1->top=p1->y()+5;
    p1->bottom=p1->y()+p1->height;
    p2->left=p2->x()+0.2*p2->width();
    p2->right=p2->x()+0.8*p2->width();
    p2->top=p2->y()+5;
    p2->bottom=p2->y()+p2->height;
    b->right=b->x+2*b->r;
    b->left=b->x;
    b->top=b->y;
    b->bottom=b->y+2*b->r;
    if(b->right>=p1->left&&b->top<=p1->bottom&&b->bottom>=p1->top&&b->right<p1->left+10)
    {
        b->x=p1->left-2*b->r;
        if(b->vx==0)
            b->vx=-1.1*p1->v;
        else
        {b->vx=-0.7*(b->vx-p1->v_run);}
        b->vy=-0.7*(b->vy-p1->jumpspeed);
    }
    if(b->left<=p1->right&&b->top<=p1->bottom&&b->bottom>=p1->top&&b->left>p1->right-10)
    {
        b->x=p1->right;
        if(b->vx==0)
            b->vx=1.1*p1->v;
        else
        {b->vx=-0.7*(b->vx-p2->v_run);}
        b->vy=-0.7*(b->vy-p2->jumpspeed);
    }
    if(b->right>=p2->left&&b->top<=p2->bottom&&b->bottom>=p2->top&&b->right<p2->left+10)
        {
            b->x=p2->left-2*b->r;
        if(b->vx==0)
                b->vx=-1.1*p2->v;
        else
        {b->vx=-0.7*(b->vx-p2->v_run);}
            b->vy=-0.7*(b->vy-p2->jumpspeed);
        }
    if(b->left<=p2->right&&b->top<=p2->bottom&&b->bottom>=p2->top&&b->left>p2->right-10)
        {
            b->x=p2->right;
        if(b->vx==0)
                b->vx=1.1*p2->v;
        else
        {b->vx=-0.7*(b->vx-p2->v_run);}
            b->vy=-0.7*(b->vy-p2->jumpspeed);
        }
        if(b->right>p2->left&&b->left<p1->right&&b->left>p1->left&&b->right<p2->right&&b->top<p1->bottom&&b->top<p2->bottom&&b->bottom>p1->top&&b->bottom>p2->top)
        {
            b->y=p1->y()-2*b->r;
            b->vy=-5;
            b->vx=0;
        }
        if(b->right>p1->left&&b->left<p2->right&&b->left>p2->left&&b->right<p1->right&&b->top<p1->bottom&&b->top<p2->bottom&&b->bottom>p1->top&&b->bottom>p2->top)
        {
            b->y=p1->y()-2*b->r;
            b->vy=-5;
            b->vx=0;
        }
        if(b->left>p1->left-b->r&&b->right<p1->right+b->r&&b->bottom>p1->top&&b->top<p1->top)
        {
            b->y=p1->top-2*b->r;
            b->vy=-0.7*(b->vy-2*p1->jumpspeed);
            b->vx=0.7*b->vx;
        }
        if(b->left>p2->left-b->r&&b->right<p2->right+b->r&&b->bottom>p2->top&&b->top<p2->top)
        {
            b->y=p2->top-2*b->r;
            b->vy=-0.7*(b->vy-2*p2->jumpspeed);
            b->vx=0.7*b->vx;
        }
        if(b->left>p1->left-b->r&&b->right<p1->right+b->r&&b->bottom==p1->bottom)
        {
            b->x=p1->right+5;
            b->vy=-5;
        }
        if(b->left>p2->left-b->r&&b->right<p2->right+b->r&&b->bottom==p2->bottom)
        {
            b->x=p2->left-2*b->r-5;
            b->vy=-5;
        }
}
void game::create_messi1()
{
    p1=new player;
    p1->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/messi1.png");
    pixmap->scaled(p1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p1->setScaledContents(true);
    p1->setPixmap(*pixmap);
    p1->setGeometry(250,620,105,130);
    p1->v=3;
    p1->height=130;
    p1->weight=105;
    p1->v_jump=9;
}
void game::create_messi2()
{

    p2=new player;
    p2->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/messi2.png");
    pixmap->scaled(p2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2->setScaledContents(true);
    p2->setPixmap(*pixmap);
    p2->setGeometry(1145,620,105,130);
    p2->v=3;
    p2->height=130;
    p2->weight=105;
    p2->v_jump=9;
}
void game::create_ronaldo1()
{

    p1=new player;
    p1->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/ronaldo1.png");
    pixmap->scaled(p1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p1->setScaledContents(true);
    p1->setPixmap(*pixmap);
    p1->setGeometry(250,605,125,145);
    p1->v=4;
    p1->height=145;
    p1->weight=125;
    p1->v_jump=13;
}
void game::create_ronaldo2()
{

    p2=new player;
    p2->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/ronaldo2.png");
    pixmap->scaled(p2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2->setScaledContents(true);
    p2->setPixmap(*pixmap);
    p2->setGeometry(1125,605,125,145);
    p2->v=4;
    p2->height=145;
    p2->weight=125;
    p2->v_jump=13;
}
void game::create_neymar1()
{

    p1=new player;
    p1->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/neymar1.png");
    pixmap->scaled(p1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p1->setScaledContents(true);
    p1->setPixmap(*pixmap);
    p1->setGeometry(250,615,110,135);
    p1->v=3;
    p1->height=135;
    p1->weight=110;
    p1->v_jump=9;
}
void game::create_neymar2()
{

    p2=new player;
    p2->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/neymar2.png");
    pixmap->scaled(p2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2->setScaledContents(true);
    p2->setPixmap(*pixmap);
    p2->setGeometry(1140,615,110,135);
    p2->v=3;
    p2->height=135;
    p2->weight=110;
    p2->v_jump=9;
}
void game::create_modric1()
{

    p1=new player;
    p1->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/modric1.png");
    pixmap->scaled(p1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p1->setScaledContents(true);
    p1->setPixmap(*pixmap);
    p1->setGeometry(250,615,105,135);
    p1->v=3;
    p1->height=135;
    p1->weight=105;
    p1->v_jump=9;
}
void game::create_modric2()
{
    p2=new player;
    p2->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/modric2.png");
    pixmap->scaled(p2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2->setScaledContents(true);
    p2->setPixmap(*pixmap);
    p2->setGeometry(1145,615,105,135);
    p2->v=3;
    p2->height=135;
    p2->weight=105;
    p2->v_jump=9;
}
void game::create_mbappe1()
{
    p1=new player;
    p1->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/mbappe1.png");
    pixmap->scaled(p1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p1->setScaledContents(true);
    p1->setPixmap(*pixmap);
    p1->setGeometry(250,610,120,140);
    p1->v=4;
    p1->height=140;
    p1->weight=120;
    p1->v_jump=11;
}
void game::create_mbappe2()
{

    p2=new player;
    p2->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/mbappe2.png");
    pixmap->scaled(p2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2->setScaledContents(true);
    p2->setPixmap(*pixmap);
    p2->setGeometry(1130,610,120,140);
    p2->v=4;
    p2->height=140;
    p2->weight=120;
    p2->v_jump=11;
}
void game::create_virgil1()
{

    p1=new player;
    p1->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/virgil1.png");
    pixmap->scaled(p1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p1->setScaledContents(true);
    p1->setPixmap(*pixmap);
    p1->setGeometry(250,600,130,150);
    p1->v=2;
    p1->height=150;
    p1->weight=130;
    p1->v_jump=12;
}
void game::create_virgil2()
{

    p2=new player;
    p2->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/virgil2.png");
    pixmap->scaled(p2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2->setScaledContents(true);
    p2->setPixmap(*pixmap);
    p2->setGeometry(1120,600,130,150);
    p2->v=2;
    p2->height=150;
    p2->weight=130;
    p2->v_jump=12;
}
void game::create_lukaku1()
{

    p1=new player;
    p1->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/lukaku1.png");
    pixmap->scaled(p1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p1->setScaledContents(true);
    p1->setPixmap(*pixmap);
    p1->setGeometry(250,600,135,150);
    p1->v=3;
    p1->height=150;
    p1->weight=135;
    p1->v_jump=10;
}
void game::create_lukaku2()
{

    p2=new player;
    p2->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/lukaku2.png");
    pixmap->scaled(p2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2->setScaledContents(true);
    p2->setPixmap(*pixmap);
    p2->setGeometry(1115,600,135,150);
    p2->v=3;
    p2->height=150;
    p2->weight=135;
    p2->v_jump=10;
}
void game::create_muller1()
{

    p1=new player;
    p1->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/muller1.png");
    pixmap->scaled(p1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p1->setScaledContents(true);
    p1->setPixmap(*pixmap);
    p1->setGeometry(250,612,115,138);
    p1->v=3;
    p1->height=138;
    p1->weight=115;
    p1->v_jump=11;
}
void game::create_muller2()
{

    p2=new player;
    p2->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/muller2.png");
    pixmap->scaled(p2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2->setScaledContents(true);
    p2->setPixmap(*pixmap);
    p2->setGeometry(1135,612,115,138);
    p2->v=3;
    p2->height=138;
    p2->weight=115;
    p2->v_jump=11;
}
void game::create_bale1()
{

    p1=new player;
    p1->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/bale1.png");
    pixmap->scaled(p1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p1->setScaledContents(true);
    p1->setPixmap(*pixmap);
    p1->setGeometry(250,607,123,143);
    p1->v=5;
    p1->height=143;
    p1->weight=123;
    p1->v_jump=10;
}
void game::create_bale2()
{

    p2=new player;
    p2->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/bale2.png");
    pixmap->scaled(p2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2->setScaledContents(true);
    p2->setPixmap(*pixmap);
    p2->setGeometry(1127,607,123,143);
    p2->v=5;
    p2->height=143;
    p2->weight=123;
    p2->v_jump=10;
}
void game::create_son1()
{

    p1=new player;
    p1->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/son1.png");
    pixmap->scaled(p1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p1->setScaledContents(true);
    p1->setPixmap(*pixmap);
    p1->setGeometry(250,608,120,142);
    p1->v=4;
    p1->height=142;
    p1->weight=120;
    p1->v_jump=10;
}
void game::create_son2()
{

    p2=new player;
    p2->setParent(this);
    QPixmap *pixmap = new QPixmap(":/new/prefix1/image/son2.png");
    pixmap->scaled(p2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p2->setScaledContents(true);
    p2->setPixmap(*pixmap);
    p2->setGeometry(1130,608,120,142);
    p2->v=4;
    p2->height=142;
    p2->weight=120;
    p2->v_jump=10;
}
