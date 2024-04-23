#ifndef KEYEVENT_H
#define KEYEVENT_H
#include<QDialog>
#include <QObject>
#include<QKeyEvent>
#include<QLabel>
class keyevent:public QDialog
{
public:
    keyevent();
    void keyPressEvent(QKeyEvent* k,QLabel*label);
};

#endif // KEYEVENT_H
