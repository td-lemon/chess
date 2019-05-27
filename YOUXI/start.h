#ifndef START_H
#define START_H
#include<QPushButton>
#include <QMainWindow>
#include"mainwindow.h"

 extern int  flag;//全局变量，1表示人人，0表示人机
class Start:public QMainWindow
{
      Q_OBJECT
public:
    Start(QWidget *parent = 0);
    ~Start();


 void paintEvent(QPaintEvent *event);

public slots:
    void tiaozhuan();
    void exit();
    void about();
    void tiaozhuan2();
    void playsound();
    void closesound();


private:

       QPushButton *p1;
       QPushButton *p2;
       QPushButton *p3;
       QPushButton *p4;
       QPushButton *p5;
       QPushButton *p6;

};

#endif // START_H
