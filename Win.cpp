#include "Headers/item.h"
#include "Headers/mainwindow.h"
#include "Headers/quanju.h"
#include "ui_mainwindow.h"
int MainWindow::chesswin(char chess_flag, int chess_i, int chess_j, int flag_jinshou)
{
    int i, j, k, num = 0;
    int sum[8];
    eight_direction(chess_i, chess_j, sum, chess_flag);
    num = 0;
    for (k = 0; k < 4; k++) {
        if (sum[k] + sum[7 - k] + 1 == 5) {
            if (chess_flag == '1')
                return 1;
            else
                return 2;
        }
        if (sum[k] + sum[7 - k] + 1 > num)
            num = sum[k] + sum[7 - k] + 1;
    }
    if (num >= 5 || flag_jinshou) {
        if (flag_jinshou == 1)
            return 4;
        else if (flag_jinshou == 2)
            return 5;
        else if (flag_jinshou == 3)
            return 6;
        else {
            if (chess_flag == '1')
                return 1;
            else
                return 2;
        }
    }
    num = 0;
    for (i = 0; i < chess_n; i++) {
        for (j = 0; j < chess_n; j++) {
            if (chess[i][j] == '0') {
                num++;
            }
        }
    }
    if (num == 0) {
        return 3;
    }
    return 0;
}
