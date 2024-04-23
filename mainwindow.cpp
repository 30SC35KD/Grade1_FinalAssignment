#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QPainter>
#include "button.h"
#include<QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1000,600);
    setWindowTitle("SoccerGoal");
    setWindowIcon(QIcon(":/new/prefix1/image/soccer (1).jpg"));
    Button*startbutton=new Button(":/new/prefix1/image/play.png");
    startbutton->setParent(this);
    startbutton->move(this->width()*0.5-startbutton->width()*0.5,this->height()*0.45);
    Preparation=new prescene;
    connect(startbutton,&Button::clicked,[=](){
        startbutton->zoomdown();
        startbutton->zoomup();
        QTimer::singleShot(350,this,[=]()
        {
            this->hide();
            Preparation->show();
        });

    });

}
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap openbackground;
    openbackground.load(":/new/prefix1/image/openbackground.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),openbackground);
}
MainWindow::~MainWindow()
{
    delete ui;
}
