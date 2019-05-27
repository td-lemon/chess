#ifndef MainWindow_H
#define MainWindow_H
#include<QPushButton>
#include <QMainWindow>
#include "GameModel.h"
#include<QTextEdit>
#include<QLabel>
#include <QPainter>
#include<QTextDocumentFragment>
#include"liststack.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = 0);
    ~MainWindow();


protected:
    // 绘制
    void paintEvent(QPaintEvent *event);   //绘制
    void mouseMoveEvent(QMouseEvent *event);// 监听鼠标移动情况，方便落子
    void mousePressEvent(QMouseEvent *event);// 实际落子
    void keyPressEvent(QKeyEvent *e); //按键盘选择黑白方
    void initPVPGame(); //初始化人人
    void initPVEGame();  //初始化人机
    void PVPhuiqi();    //人人悔棋
    void PVEhuiqi();   //人机悔棋
    void panduan();     //判断胜负

private:
    GameModel *game; // 游戏指针
    GameType game_type; // 存储游戏类型
    int clickPosRow, clickPosCol; // 存储将点击的位置
    void checkGame(int y, int x);
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;

    QPushButton *bt1;
    QPushButton *bt2;
    QPushButton *bt3;
      QPushButton *bt4;
     QPainter *paint;
     int pr;
     int pl;
     int air;
     int ail;
     ListStack s;
     QTimer *t;


private slots:
    void chessOneByPerson(); // 人执行
    void chessOneByAI(); // AI下棋
    void initGame();  //初始化
    void submit();   //投降
    void huiqi();    //悔棋
    void exit();    //结束
   // void save();
    void back();    //返回
    void time();    //计时
    //void restore();
};





#endif // MainWindow_H
