#include"Headers/quanju.h"
#include"Headers/item.h"
#include"Headers/mainwindow.h"
#include "ui_mainwindow.h"
void three_change( ) {
    printf("是否选择与黑方交换 [Y/N] : ");
    char ch;
    scanf("%c", &ch,1);
    while (ch != 'Y' && ch != 'N') {
        printf("error\n");
        scanf("%c", &ch,1);
    }
    if (ch == 'Y') {
        printf("交换成功！！！\n");
    }
}
int five_n_hit(int n) {
    printf("---------------Black Round---------------\n");
    printf("五 手 %d 打\n",n);
    int i, k, x, y;
    int a[100][2],len=0;
    for (i = 0; i < n; i++) {
        while (1) {
            printf("输入落子位置： ");
            scanf("%d%d", &x, &y);
            if (x >= 0 && x < chess_n && y >= 0 && y < chess_n && chess[x][y] == '0') {
                chess[x][y] = '1';
                a[len][0] = x, a[len][1] = y;
                len++;
                break;
            }
            else {
                printf("Error address, Please re-enter !\n");
                printf("\a");
            }
        }
    }
    while (1) {
        printf("输入保留的黑棋位置 ： ");
        scanf("%d%d", &x, &y);
        for (i = 0; i < n; i++) {
            if (a[i][0] == x && a[i][1] == y) {
                k = i;
                goto ikun;
            }
        }
        printf("error !!!\n");
    }
    ikun:
    for (i = 0; i < n; i++) {
        if (i != k)  chess[a[i][0]][a[i][1]] = '0';
    }
    x = a[k][0], y = a[k][1];
    Fchess[Fchess_len].x = x;
    Fchess[Fchess_len].y = y;
    Fchess_len++;
    if (MainWindow::chesswin('1', x, y, 0)) return 1;
    return 0;
}
