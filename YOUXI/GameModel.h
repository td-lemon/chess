#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// ---- 五子棋游戏模型类 ---- //
#include <vector> //能够操作多种数据结构和算法的模板类和函数库,vector可以认为是一个能够存放任意类型的动态数组，能够增加和压缩数据。
#include"liststack.h"
#include<time.h>

// 游戏类型，双人还是AI（目前固定让AI下黑子）
enum GameType //枚举类型的定义中列举出所有可能的取值，被说明为该“枚举”类型的变量取值不能超过定义的范围,例如一周七天
{
    PERSON,
    BOT
};

// 游戏状态
enum GameStatus
{
    PLAYING,
    WIN,
    DEAD
};

// 棋盘尺寸
const int kBoardSizeNum = 15;
class GameModel
{
public:
     GameModel();
     ListStack s;
public:
    std::vector<std::vector<int>> gameMapVec; // 使用容器 存储当前游戏棋盘和棋子的情况,空白为0，白子1，黑子-1，相当于二维数组
    std::vector<std::vector<int>> scoreMapVec; // 存储各个点位的评分情况，作为AI下棋依据
    bool playerFlag; // 标示下棋方
    GameType gameType; // 游戏模式
    GameStatus gameStatus; // 游戏状态
    void startGame(GameType type); // 开始游戏
    void calculateScore(); // 计算评分
    void actionByPerson(int row, int col); // 人执行下棋
    void actionByAI(int &clickRow, int &clickCol); // 机器执行下棋
    void updateGameMap(int row, int col); // 每次落子后更新游戏棋盘
    bool isWin(int row, int col); // 判断游戏是否胜利
    bool isDeadGame(); // 判断是否和棋  
};
#endif // GAMEMODEL_H
