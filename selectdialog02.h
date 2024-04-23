#ifndef SELECTDIALOG02_H
#define SELECTDIALOG02_H
#include"playerbutton.h"
#include <QMainWindow>

class selectdialog02 : public QMainWindow
{
    Q_OBJECT
public:
    explicit selectdialog02(QWidget *parent = nullptr);
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

#endif // SELECTDIALOG02_H
