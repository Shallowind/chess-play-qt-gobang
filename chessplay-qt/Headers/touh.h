#ifndef TOUH_H
#define TOUH_H

#include <iostream>
using namespace std;
#include <QDebug>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QString>
#include <conio.h>
#include <cstdio>
#include <stack>
#include <time.h>
#include <vector>
#include <windows.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class FFchess {
public:
    int x, y;
};

#define five_n 2
void rules(int x); // 规则
void printfchess(); // 打印棋盘
int chesswin(char chess_flag, int chess_i, int chess_j, int flag_jinshou); // 判断胜利
void initchess(); // 初始化棋盘
int huiqi(); // 悔棋
int luozi(char op); // 人落子
int luoziAI(char op); // AI落子
void chessop0(); // 复盘
void chessop1(); // 双人对战
void chessop2(); // 人机对战
void control();
int ChessScore(int lian, int x, int y, char opr, int mode);
int jinshou(int chess_i, int chess_j); // 禁手
void eight_direction(int chess_i, int chess_j, int sum[], char chess_flag);
void three_change();
int five_n_hit(int n);
#endif // TOUH_H
