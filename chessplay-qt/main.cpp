#include "Headers/form.h"
#include "Headers/mainwindow.h"
#include "Headers/touh.h"
#include <iostream>
using namespace std;
#include <QApplication>
FFchess Fchess[24 * 24];
int chess_n = 15;
int Fchess_len;
char chess[24][24];
char chess_jin[24][24];
int score1[24][24];
int score2[24][24];
int X1, Y1, X2, Y2;
int num_step;
int chessjudge[20];
int text1, text2, fupan = -1;
char aiop = '0';
int value_jinshou = 1, ikun = 0;
int sanshoujiaohuan = 0, wushouliangda = 0, wushou_flag = 0,yin=1;
QVector<Item> items;
QVector<Item> xitems;
char op;
// 0空  1黑  2白
int main(int argc, char* argv[])
{
    initchess();
    QApplication a(argc, argv);

    Form* f = new Form();
    f->show();

    return a.exec();
}
