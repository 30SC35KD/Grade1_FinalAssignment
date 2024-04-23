#ifndef MESSI1_H
#define MESSI1_H
#include<QPushBUtton>
#include <QObject>
#include <QWidget>
#include"game.h"
#include"player.h"
class messi1 : public QPushButton
{
    Q_OBJECT
public:
    //explicit messi1(QWidget *parent = nullptr);
    game*g;
    messi1(game*g);
signals:
};

#endif // MESSI1_H
