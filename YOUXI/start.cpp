#include "mainwindow.h"
#include"start.h"
#include<QPainter>
#include<QApplication>
#include<QMessageBox>
#include<stdio.h>
#include<QSound>
 int  flag;
 QSound *sound=new QSound("E:/QT/test/YOUXI/music.wav");
Start::Start(QWidget *parent)
 : QMainWindow(parent)
{
    this-> resize(1000,800);
    this->setWindowTitle("五子棋");

    QFont font("华文行楷",38,65);
    QFont font2("黑体",20,20);

    p1=new QPushButton(this);
    p1->setGeometry(350,450,280,80);
    p1->setText("人机对战");
    p1->setFont(font);

    p2=new QPushButton(this);
    p2->setGeometry(350,530,280,80);
    p2->setText("人人对战");
    p2->setFont(font);

    p3=new QPushButton(this);
    p3->setGeometry(350,610,280,80);
    p3->setText("退出");
    p3->setFont(font);

    p4=new QPushButton(this);
    p4->setGeometry(350,690,280,80);
    p4->setText("关于");
    p4->setFont(font);


    p5=new QPushButton(this);
    p5->setGeometry(350,370,280,80);
    p5->setText("音效");
    p5->setFont(font);

    p6=new QPushButton(this);
    p6->setGeometry(800,700,120,50);
    p6->setText("关闭音效");
    p6->setFont(font2);


    QPalette   pal;
    pal.setColor(QPalette::ButtonText, QColor(230,0,0));

    p1->setPalette(pal);
    p2->setPalette(pal);
    p3->setPalette(pal);
    p4->setPalette(pal);
    p5->setPalette(pal);



    p1->setStyleSheet("background-color: rgb(200,195,170)");
    p2->setStyleSheet("background-color: rgb(200,195,170)");
    p3->setStyleSheet("background-color: rgb(200,195,170)");
    p4->setStyleSheet("background-color: rgb(200,195,170)");
    p5->setStyleSheet("background-color: rgb(200,195,170)");
   p6->setStyleSheet("background-color: rgb(200,195,170)");


    connect( p1,SIGNAL(clicked(bool)),this,SLOT(tiaozhuan2()));
    connect( p2,SIGNAL(clicked(bool)),this,SLOT(tiaozhuan()));
    connect( p3,SIGNAL(clicked(bool)),this,SLOT(exit()));
    connect( p4,SIGNAL(clicked(bool)),this,SLOT(about()));
    connect( p5,SIGNAL(clicked(bool)),this,SLOT(playsound()));
    connect( p6,SIGNAL(clicked(bool)),this,SLOT(closesound()));

}

void Start::playsound()
{
      sound->setLoops(5000);// 循环播放
      sound->play();

}

void Start::closesound()
{

     sound->stop();
}

void Start::tiaozhuan()
{

    hide();
    flag=1;
    printf( "flag=%d",flag);
    MainWindow *w = new MainWindow;
    w->show();
}

void Start::tiaozhuan2()
{
    hide();
     flag=0;
    MainWindow *w = new MainWindow;
    w->show();

}

void Start::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);;
    painter.drawPixmap(0,0,1000,800,QPixmap("E:/QT/test/YOUXI/5.jpg"));//插图

}

Start::~Start()
{
}

void Start::exit()
{
    QApplication *app;
    app->exit(0);
}

void Start::about()
{
     QMessageBox::about(NULL,"关于","无敌五子棋v1.0 制作者:刘杰");
}


