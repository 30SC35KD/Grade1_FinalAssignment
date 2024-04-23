#include "keyevent.h"
#include"game.h"
#include<QLabel>
keyevent::keyevent() {}
void keyevent::keyPressEvent(QKeyEvent *k)
{
    //获取label所在的当前位置
    int x = label2->pos().x();
    int y = label->pos().y();
    if(k->key() == Qt::Key_Left){//左
        label->move(x-10,y);
    }
    else if(k->key() == Qt::Key_Right){//右
        label->move(x+10,y);
    }
    else if(k->key() == Qt::Key_Up){//上
        label->move(x,y-10);
    }

}

