#ifndef CHOOSEBUTTON1_H
#define CHOOSEBUTTON1_H
#include "qpushbutton.h"
#include <QString>
class choosebutton1:public QPushButton
{
public:
    choosebutton1(QString beforeImgPath,QString afterImgPath="");
    QString beforeImgPath;
    QString afterImgPath;
    void zoomdown();
    void zoomup();
};

#endif // CHOOSEBUTTON1_H
