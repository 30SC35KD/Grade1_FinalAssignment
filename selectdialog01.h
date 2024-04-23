#ifndef SELECTDIALOG01_H
#define SELECTDIALOG01_H
#include"playerbutton.h"
#include <QMainWindow>

class selectdialog01 : public QMainWindow
{
    Q_OBJECT
public:
    explicit selectdialog01(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    playerbutton *messi;
    playerbutton *ronaldo;
    playerbutton *neymar;
    playerbutton *mbappe;
    playerbutton *modric;
    playerbutton *virgil;
    playerbutton *lukaku;
    playerbutton *bale;
    playerbutton *muller;
    playerbutton *son;
signals:
};

#endif // SELECTDIALOG01_H
