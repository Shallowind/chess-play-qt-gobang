#ifndef QUANJU_H
#define QUANJU_H

#endif // QUANJU_H
#include "Headers/item.h"
#include "touh.h"
extern FFchess Fchess[24 * 24];
extern int Fchess_len;
extern char chess[24][24], aiop, op;
extern char chess_jin[24][24];
extern int score1[24][24];
extern int score2[24][24];
extern int X1, Y1, X2, Y2, text1, text2, fupan, num_step, chess_n, value_jinshou, sanshoujiaohuan, wushouliangda;
extern int chessjudge[20], wushou_flag, ikun,yin;
extern QVector<Item> items;
extern QVector<Item> xitems;
