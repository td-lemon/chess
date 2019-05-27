#include <QPainter>
#include <QTimer>
#include <QSound>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <math.h>
#include<stdio.h>
#include<QApplication>
#include "mainwindow.h"
#include<QImageWriter>
#include<QImageReader>
#include"start.h"
#include"liststack.h"
#include<iostream>
// -------全局遍历-------//
#define CHESS_ONE_SOUND ":/chessone.wav"
#define WIN_SOUND ":/win.wav"
#define LOSE_SOUND ":/lose.wav"
const int kBoardMargin = 30; // 棋盘边缘空隙
const int kRadius = 15; // 棋子半径
const int kMarkSize = 6; // 落子标记边长
const int kBlockSize = 40; // 格子的大小
const int kPosDelta = 20; // 鼠标点击的模糊距离上限
const int kAIDelay = 700; // AI下棋的思考时间
extern int  flag;
int timeCounts=0;

MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow(parent)
{



    this->setWindowTitle("五子棋");//标题
    this->resize(kBoardMargin * 2 + kBlockSize * kBoardSizeNum+200, kBoardMargin * 2 + kBlockSize * kBoardSizeNum);


  //edit1=new QTextEdit(this);
  //edit1->setGeometry(638,5,322,627);
  //edit1->setStyleSheet("background-color:lightblue");

    /*QTextDocumentFragment fragment;
     fragment = QTextDocumentFragment::fromHtml("<img src='E:/QT/test/MainWindow/timg.jpg'>");
               edit1->textCursor().insertFragment(fragment);
               edit1->setVisible(true);*/



   //edit1->setStyleSheet("background-image:url(:/QT/testYOUXI/2.jpg);");

   /* QPalette pa;
    this->setAutoFillBackground(true);
    QPixmap  pixmap (":/2.jpg");
    pa.setBrush(QPalette::Window, QBrush(pixmap));
    edit1->setPalette(pa);*/

    QFont font2("Microsoft YaHei",20,65);
    bt1=new QPushButton(this);
    bt1->setText("退出");
    bt1->setFont(font2);
    bt1->setGeometry(703,555,88,58);
    connect( bt1,SIGNAL(clicked(bool)),this,SLOT(exit()));

    bt2=new QPushButton(this);
    bt2->setText("悔棋");
    bt2->setFont(font2);
    bt2->setGeometry(703,485,88,58);
    connect( bt2,SIGNAL(clicked(bool)),this,SLOT(huiqi()));

    bt3=new QPushButton(this);
    bt3->setText("重玩");
    bt3->setFont(font2);
    bt3->setGeometry(703,415,88,58);

    connect(bt3,SIGNAL(clicked(bool)),this,SLOT(initGame()));


    bt4=new QPushButton(this);
    bt4->setText("返回");
    bt4->setFont(font2);
    bt4->setGeometry(703,345,88,58);

    connect(bt4,SIGNAL(clicked(bool)),this,SLOT(back()));



    label1=new QLabel(this);
    label1->setGeometry(723,0,78,358);
    QFont font("Microsoft YaHei",30,75);
    label1->setFont(font);
    label1->setWordWrap(true);//文字换行


    QFont font3("Microsoft YaHei",20,65);
    label2=new QLabel(this);
    label2->setGeometry(200, kBoardMargin * 2 + kBlockSize * kBoardSizeNum-60,248,48);
    label2->setFont(font3);
    label2->setText("本次游戏时间：");

    label3=new QLabel(this);
    label3->setGeometry(400, kBoardMargin * 2 + kBlockSize * kBoardSizeNum-50,88,28);
    label3->setFont(font3);


     // 设置棋盘大小
     //setFixedSize(kBoardMargin * 2 + kBlockSize * kBoardSizeNum, kBoardMargin * 2 + kBlockSize * kBoardSizeNum);

     // 设置背景颜色
     // QPalette Pal(palette());
     // Pal.setColor (QPalette::Background, QColor (210, 76, 60));
     // this->setAutoFillBackground(true);
     //  this->setPalette(Pal);
     // this->show();

    //this->setStyleSheet("background-color:#F5BC6B;");

    // 开启鼠标hover功能，这两句一般要设置window的
    setMouseTracking(true);
    setCursor(Qt::PointingHandCursor);//设置鼠标形状
    //centralMainWindow()->setMouseTracking(true);

    // 添加菜单
    QMenu *Menu1 = menuBar()->addMenu(tr("选择")); // menuBar默认是存在的，直接加菜单就可以了
    QAction *action1 = new QAction("投降", this);
    connect(action1, SIGNAL(triggered()), this, SLOT(submit()));
    Menu1->addAction(action1);

    QAction *action2 = new QAction("退出", this);
    connect(action2, SIGNAL(triggered()), this, SLOT(exit())); 
    Menu1->addAction(action2);

    QAction *action3 = new QAction("保存", this);
    connect(action3, SIGNAL(triggered()), this, SLOT(save()));
    Menu1->addAction(action3);

    QAction *action4 = new QAction("读取", this);
    connect(action4, SIGNAL(triggered()), this, SLOT(restore()));
    Menu1->addAction(action4);

    t =new QTimer(this);
    t->start(1000);
    connect(t,SIGNAL(timeout()),this,SLOT(time()));


    // 开始游戏
    initGame();
}

void MainWindow::submit()
{
    if(game->playerFlag)
    {
        QMessageBox::information(NULL, "提示", "恭喜黑子胜利");
        initPVPGame();
        initPVEGame();
    }
    else
       QMessageBox::information(NULL, "提示", "恭喜白子胜利");
       initPVPGame();
}

MainWindow::~MainWindow()
{
    if (game)
    {
        delete game;
        game = nullptr;
    }

}

void MainWindow::initGame()
{
    // 初始化游戏模型
    //i1=0;
    //j1=0;
    pr=-1;
    pl=-1;
    air=-1;
    ail=-1;;
    game = new GameModel;
     timeCounts=0;
     t->start(1000);
     label1->setText("请按键选黑:1 白:2");


    if(flag==1)
        {
        initPVPGame();
        }
    else
    if(flag==0)
      {
       initPVEGame();
      }

}

void MainWindow::initPVPGame()
{
    game_type = PERSON;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();

}

void MainWindow::initPVEGame()
{
    game_type = BOT;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    QPen pen; // 调整线条宽度
    pen.setWidth(2);
    painter.setPen(pen);

    painter.drawPixmap(kBoardMargin*2+kBlockSize * kBoardSizeNum,0,198,kBoardMargin*2+kBlockSize * kBoardSizeNum,QPixmap("E:/QT/test/YOUXI/right.jpg"));//插图

     painter.drawPixmap(0,0,kBoardMargin*2+kBlockSize * kBoardSizeNum,kBoardMargin*2+kBlockSize * kBoardSizeNum,QPixmap("E:/QT/test/YOUXI/background.jpg"));//背景插图

    for (int i = 0; i < kBoardSizeNum ; i++)
    {

        painter.drawLine(kBoardMargin + kBlockSize * i, kBoardMargin, kBoardMargin + kBlockSize * i, size().height()-kBoardMargin-kBlockSize );// 竖线
        painter.drawLine(kBoardMargin, kBoardMargin + kBlockSize * i, size().width() - kBoardMargin-200-kBlockSize, kBoardMargin + kBlockSize * i);//横线
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    // 绘制落子标记(防止鼠标出框越界)
    if (clickPosRow >=0 && clickPosRow <kBoardSizeNum &&
        clickPosCol >=0 && clickPosCol <kBoardSizeNum &&
        game->gameMapVec[clickPosRow][clickPosCol] == 0)
    { 
        if (game->playerFlag)
            {
             brush.setColor(Qt::white);
             {
              label1->setText("白方下棋");              
             }
            }
        else
            {
             brush.setColor(Qt::black);
             label1->setText("黑方下棋");
            }
        painter.setBrush(brush);
        painter.drawRect(kBoardMargin + kBlockSize * clickPosCol - kMarkSize / 2, kBoardMargin + kBlockSize * clickPosRow - kMarkSize / 2, kMarkSize, kMarkSize);
    }

    // 绘制棋子
    for (int i = 0; i < kBoardSizeNum; i++)
        for (int j = 0; j < kBoardSizeNum; j++)
            {
             if (game->gameMapVec[i][j] == 1)
            {

              //brush.setColor(Qt::white);
              //painter.setBrush(brush);

              //painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
               painter.drawPixmap(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius,kRadius * 2,kRadius * 2,QPixmap("E:/QT/test/YOUXI/white.png"));

            }
            else if (game->gameMapVec[i][j] == -1)
            {
               // brush.setColor(Qt::black);
                //painter.setBrush(brush);
                //.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
                     painter.drawPixmap(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius,kRadius * 2,kRadius * 2,QPixmap("E:/QT/test/YOUXI/black.png"));
            }

          }
         panduan();



}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

    // 棋盘边缘不能落子
    if (x >= kBoardMargin&&
            x < kBoardMargin+kBlockSize*kBoardSizeNum&&
            y >=  kBoardMargin &&
            y < kBoardMargin+kBlockSize*kBoardSizeNum)
    {
        // 获取一个格子最近的左上角的点
        int col = x / kBlockSize;//鼠标的横坐标除以格子大小
        int row = y / kBlockSize;

        int leftTopPosX = kBoardMargin + kBlockSize * col;//最近左上角的横坐标
        int leftTopPosY = kBoardMargin + kBlockSize * row;

        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        clickPosRow = -1; // 初始化最终的值
        clickPosCol = -1;
        int len = 0; // 计算完后取整就可以了

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }
    }

    // 存了坐标后也要重绘
    update();



}

void MainWindow::mousePressEvent(QMouseEvent *event)
{


    // 人下棋，并且不能抢机器的棋
    if (!(game->gameType == BOT && !(game->playerFlag)))
    {
       chessOneByPerson();
    }

        // 如果是人机模式，需要调用AI下棋
    if(game->gameType == BOT && !(game->playerFlag))

       {

            chessOneByPerson();
            QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));// 用定时器做一个延迟
       }

    //i1= clickPosRow;
    //j1=clickPosCol;
   // printf("i1=%d",clickPosRow);
   // printf( "j1=%d",clickPosCol);
}

void MainWindow::chessOneByPerson()
{
    // 根据当前存储的坐标下子
    // 只有有效点击才下子，并且该处没有子
    if (clickPosRow != -1 && clickPosCol != -1 && game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        game->actionByPerson(clickPosRow, clickPosCol);
       // i1= clickPosRow;
      //  j1=clickPosCol;
       QSound::play(CHESS_ONE_SOUND);

        // 重绘
       s.push(clickPosCol);
       s.push(clickPosRow);
        update();
    }
}

void MainWindow::chessOneByAI()
{
    game->actionByAI(clickPosRow, clickPosCol);
    //i1= clickPosRow;
    //j1=clickPosCol;
    QSound::play(CHESS_ONE_SOUND);
    s.push(clickPosCol);
    s.push(clickPosRow);
    update();  
}

void MainWindow::PVPhuiqi()
{



               //if((i1 > 0 && i1 < kBoardSizeNum &&
                // j1 > 0 && j1 < kBoardSizeNum))
           int r;
           int l;
           int m;
        if(s.get_top(m))
        {
           if(s.get_top(r))
           {
            pr=r;
            s.pop();
           }
           if(s.get_top(l))
           {
            pl=l;
            s.pop();
           }
        }

       game->gameMapVec[pr][pl] = 0;
       game->playerFlag =!game->playerFlag;
       update();


}

void MainWindow::PVEhuiqi()
 {

             //if((i1 > 0 && i1 < kBoardSizeNum &&
              // j1 > 0 && j1 < kBoardSizeNum))
                    int r;
                    int l;
                    int m;
                    int r1;
                    int l1;
               if(s.get_top(m))
               {
                   if(s.get_top(r))
                       {
                         air=r;
                         s.pop();
                       }
                   if(s.get_top(l))
                      {
                        ail=l;
                       s.pop();
                      }
                    if(s.get_top(r1))
                       {
                        pr=r1;
                        s.pop();
                       }
                   if(s.get_top(l1))
                       {
                        pl=l1;
                        s.pop();
                        }
                  game->gameMapVec[air][ail] = 0;
                  game->gameMapVec[pr][pl] = 0;
                  update();

                   // game->gameMapVec[i1][j1] = 0;
                }

}

void MainWindow::huiqi()
{
     if(game_type == PERSON )
     {
         PVPhuiqi();
     }else
     {
         PVEhuiqi();
     }
}

void MainWindow::exit()
{
    QApplication *app;
    app->exit(0);
}

void MainWindow::back()
{
    hide();
    t->stop();
    Start *s=new Start;
    flag=-1;
    s->show();
}

void MainWindow::panduan()
{
    // 判断输赢
    if (clickPosRow >=0 && clickPosRow <kBoardSizeNum &&
        clickPosCol >=0 && clickPosCol < kBoardSizeNum &&
        (game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
            game->gameMapVec[clickPosRow][clickPosCol] == -1))
    {
        if (game->isWin(clickPosRow, clickPosCol) && game->gameStatus == PLAYING)
        {

            qDebug() << "win";
            game->gameStatus = WIN;
            QSound::play(WIN_SOUND);
            QString str;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                str = "白子";
            else if (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                str = "黑子";
            t->stop();
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "恭喜", str + "胜利!");

            // 重置游戏状态，否则容易死循环
            if (btnValue == QMessageBox::Ok)
            {
                game->startGame(game_type);
                game->gameStatus = PLAYING;


            }
        }
    }


    // 判断死局
    if (game->isDeadGame())
    {

        QSound::play(LOSE_SOUND);
        t->stop();
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "提示", "死局!");
        if (btnValue == QMessageBox::Ok)
        {
            game->startGame(game_type);
            game->gameStatus = PLAYING;

        }

    }
}

/*void MainWindow::save()
{
  QPainter p(this);
    p.save();
}*/

/*void MainWindow::restore()
{
  QPainter p(this);
    p.restore();
}*/

void MainWindow::time()
{

    timeCounts++;
    label3->setText(QString::number(timeCounts)+"秒");

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    int key=e->key();
    switch(key)
    {
       case Qt::Key_1:
    {
                game->playerFlag=!game->playerFlag;
                 break;
    }


    case Qt::Key_2:break;

    }
}





