#include"Headers/quanju.h"
#include"Headers/item.h"
#include"Headers/mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::chessop1() {
    //printfchess();
    //cout<<1;
    //ui->lineEdit->setText("123");
    int num = 0;
    while (0) {
        /*if (num == 4) {
            if (five_n_hit(five_n)) break;
        }
        else if (luozi('1')) break;
        num++;
        if (num == 3) three_change();
        if (luozi('2')) break;
        num++;*/
    }
    luozi('1');
    luozi('2');
}
int MainWindow::luozi(char op) {
    //ui->lineEdit->setText(QString::number(text1));
    //ui->lineEdit_2->setText(QString::number(text2));
    return  0;
    int x, y, num_huiqi = 0, flag_jinshou;
    //if (op == '1') printf("---------------Black Round---------------\n");
    //else printf("---------------White Round---------------\n");
    while (num_huiqi <= 1) {
        while (1) {
            //printf("输入落子位置： \n");
            //scanf("%d%d", &x, &y);
            x=text1;y=text2;
            flag_jinshou = 0;
            if(x >= 0 && x < chess_n && y >= 0 && y < chess_n && chess[x][y] == '0') {
                if (op == '1') flag_jinshou = jinshou(x, y);
                if (flag_jinshou) {
                    printf("禁手  ");
                    if (flag_jinshou == 1) printf("长连");
                    else if (flag_jinshou == 2) printf("四四");
                    else printf("三三"); printf("禁手 ");
                }
                else
                {
                    chess[x][y] = op;
                    break;
                }
            }else{
                printf("Error address, Please re-enter !\n");
                printf("\a");
            }
        }
        printfchess();
        if (num_huiqi < 1 && huiqi()) {
            num_huiqi++;
            chess[x][y] = '0';
            printfchess();
        }
        else break;
    }
    Fchess[Fchess_len].x = x;
    Fchess[Fchess_len].y = y;
    Fchess_len++;
    if (chesswin(op, x, y, flag_jinshou)) return 1;
    return 0;
}
