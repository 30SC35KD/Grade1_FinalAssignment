#ifndef PRESCENE_H
#define PRESCENE_H
#include"selectbutton1.h"
#include <QMainWindow>
#include<QPaintEvent>
#include"kickoff.h"
#include"game.h"
#include<QObject>
class prescene : public QMainWindow
{
    Q_OBJECT
public:
    explicit prescene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    selectbutton1*selectbutton0;
    selectbutton1*selectbutton;
    kickoff*kick_off;
    game*g;
signals:
};

#endif // PRESCENE_H
