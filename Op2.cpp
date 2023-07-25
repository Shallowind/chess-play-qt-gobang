#include "Headers/item.h"
#include "Headers/mainwindow.h"
#include "Headers/quanju.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
void chessop2()
{
    // cout << "请选择执棋颜色" << endl;
    // cout << "1.黑棋" << endl;
    // cout << "2.白棋" << endl;
    // cout << "注意：黑棋第一步必定在棋盘正中间落子" << endl;
    int op = 1;
    // cin >> op;
    // chess[(chess_n - 1) / 2][(chess_n - 1) / 2] = '1';
    Fchess[Fchess_len].x = (chess_n - 1) / 2;
    Fchess[Fchess_len].y = (chess_n - 1) / 2;
    Fchess_len++;
    if (op == 1) {
        // luoziAI('2');
        // printfchess();
        while (1) {
            // if (luozi('1')) break;
            // if (luoziAI('2')) break;
        }
    } else {
        // printfchess();
        // luozi('2');
        while (1) {
            // if (luoziAI('1')) break;
            // if (luozi('2')) break;
        }
    }
}
void ChessCon(char opr, int& maxsc)
{
    int i, j, k, score = 0, sum = 1;
    for (i = 0; i < chess_n; i++) {
        for (j = 0; j < chess_n; j++) {
            chess_jin[i][j] = chess[i][j];
        }
    }
    if (opr == '1') {
        for (i = 0; i < chess_n; i++) {
            for (j = 0; j < chess_n; j++) {
                chess_jin[i][j] = chess[i][j];
            }
        }
    }
    for (i = 0; i < chess_n; i++) {
        for (j = 0; j < chess_n; j++) {
            if (chess[i][j] != '0')
                continue;
            if (opr == '1' && value_jinshou == 1 && jinshou(i, j))
                continue;
            sum = 1;
            for (k = 1; k <= 4; k++) {
                if (i + k >= chess_n)
                    break;
                if (chess[i + k][j] == opr)
                    sum++;
                else
                    break;
            }
            for (k = 1; k <= 4; k++) {
                if (i - k < 0)
                    break;
                if (chess[i - k][j] == opr)
                    sum++;
                else
                    break;
            }
            score = ChessScore(sum, i, j, opr, 2); // 竖着
            sum = 1;
            for (k = 1; k <= 4; k++) {
                if (j + k >= chess_n)
                    break;
                if (chess[i][j + k] == opr)
                    sum++;
                else
                    break;
            }
            for (k = 1; k <= 4; k++) {
                if (j - k < 0)
                    break;
                if (chess[i][j - k] == opr)
                    sum++;
                else
                    break;
            }
            score = ChessScore(sum, i, j, opr, 1); // 横着
            sum = 1;
            for (k = 1; k <= 4; k++) {
                if (i + k >= chess_n || j + k >= chess_n)
                    break;
                if (chess[i + k][j + k] == opr)
                    sum++;
                else
                    break;
            }
            for (k = 1; k <= 4; k++) {
                if (i - k < 0 || j - k < 0)
                    break;
                if (chess[i - k][j - k] == opr)
                    sum++;
                else
                    break;
            }
            score = ChessScore(sum, i, j, opr, 3); // 左上右下
            sum = 1;
            for (k = 1; k <= 4; k++) {
                if (i + k >= chess_n || j - k < 0)
                    break;
                if (chess[i + k][j - k] == opr)
                    sum++;
                else
                    break;
            }
            for (k = 1; k <= 4; k++) {
                if (i - k < 0 || j + k >= chess_n)
                    break;
                if (chess[i - k][j + k] == opr)
                    sum++;
                else
                    break;
            }
            score = ChessScore(sum, i, j, opr, 4); // 左下右上
            for (int po = 0; po < 20; po++)
                chessjudge[po] = 0;
            if (opr == '1') {
                maxsc = max(maxsc, score1[i][j]);
            }
            if (opr == '2') {
                score2[i][j] = score;
                maxsc = max(maxsc, score);
            }
            score = 0;
        }
        cout << endl;
    }
}
int MainWindow::luoziAI(char op)
{
    int x, y, num_huiqi = 0, maxsc1 = 0, maxsc2 = 0;
    // if (op == '1') printf("---------------Black Round---------------\n");
    // else printf("---------------White Round---------------\n");
    // system("cls");
    int a[chess_n * chess_n][2] = { 0 }, b[chess_n * chess_n][2] = { 0 };
    int m = -1, n = -1;
    ChessCon('1', maxsc1);
    ChessCon('2', maxsc2);
    for (int i = 0; i < chess_n; i++) {
        for (int j = 0; j < chess_n; j++) {
            if (maxsc1 < score1[i][j])
                maxsc1 = score1[i][j];
            if (maxsc1 < score2[i][j])
                maxsc2 = score2[i][j];
        }
    }

    // maxsc1 = 0; maxsc2 = 0;
    for (int i = 0; i < chess_n; i++) {
        for (int j = 0; j < chess_n; j++) {
            if (score1[i][j] == maxsc1) {
                // maxsc1 = score1[i][j];
                m++;
                a[m][0] = i;
                a[m][1] = j;
                X1 = i;
                Y1 = j;
            }
            if (score1[i][j] != 1)
                cout << score1[i][j] << " ";
            else
                cout << "  ";
            score1[i][j] = 0;
            // score2[i][j] = 0;
        }
        cout << endl;
    }
    cout << endl;

    srand((unsigned)time(NULL));
    int rand1 = rand() % (m + 1);

    X1 = a[rand1][0];
    Y1 = a[rand1][1];
    for (int i = 0; i < chess_n; i++) {
        for (int j = 0; j < chess_n; j++) {
            if (score2[i][j] == maxsc2) {
                // maxsc2 = score2[i][j];
                n++;
                b[n][0] = i;
                b[n][1] = j;
                X2 = i;
                Y2 = j;
            }
            if (score2[i][j] != 1)
                cout << score2[i][j] << " ";
            else
                cout << "  ";
            score1[i][j] = 0;
            score2[i][j] = 0;
        }
        cout << endl;
    }
    cout << endl;
    srand((unsigned)time(NULL));
    int rand2 = rand() % (n + 1);
    X2 = b[rand2][0];
    Y2 = b[rand2][1];
    srand((unsigned)time(NULL));
    int rand3 = rand() % (2);
    if (maxsc1 > maxsc2) {
        x = X1;
        y = Y1;
    } else if (maxsc1 < maxsc2) {
        x = X2;
        y = Y2;
    } else {
        if (maxsc1 >= 11) { // 大优势优先进攻
            if (op == '1') {
                x = X1;
                y = Y1;
            } else {
                x = X2;
                y = Y2;
            }
        } else { // 随机攻防
            cout << rand3;
            if (rand3 == 0) {
                x = X2;
                y = Y2;
            } else {
                x = X1;
                y = Y1;
            }
        }
    }
    text1 = x;
    text2 = y;
    cout << maxsc1 << "  " << maxsc2 << endl;
    /*if(op=='1'&&flagai==0){
        flagai=1;
        x=7;y=7;
    }*/
    QPoint pt;
    pt.setX(y);
    pt.setY(x);
    Item item(pt, op); // 设定棋子坐标及颜色
    items.append(item); // 添加棋子到所有的棋子Q
    chess[x][y] = op;
    chess_jin[x][y] = op;
    QString strTip;
    int win = chesswin(op, pt.y(), pt.x(), 0);
    if (win == 1) {
        winplayer->play();
        for (int i = 0; i < items.size(); i++) {
            xitems.append(items[i]);
        }
        ui->fupan->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->exit->setVisible(false);
        ui->tishi->setVisible(false);
        ui->huiqi->setVisible(false);
        strTip = "黑棋胜利！";

        ui->lable->setText("请选择游戏模式");
        QMessageBox::information(this, "游戏结束", strTip, QMessageBox::Yes);
        items.clear();
        initchess();
        aiop = '4';
        // flagai=0;
        // ui->lable_3->setText("black winner !!!\n\n");
    } else if (win == 2 || win == 4 || win == 5 || win == 6) {
        winplayer->play();
        for (int i = 0; i < items.size(); i++) {
            xitems.append(items[i]);
        }
        ui->fupan->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->exit->setVisible(false);
        ui->tishi->setVisible(false);
        ui->huiqi->setVisible(false);

        if (win == 2)
            strTip = "白棋胜利！";
        else if (win == 4)
            strTip = "白棋胜利！黑方触犯长连禁手";
        else if (win == 5)
            strTip = "白棋胜利！黑方触犯四四禁手";
        else if (win == 6)
            strTip = "白棋胜利！黑方触犯三三禁手";
        ui->lable->setText("请选择游戏模式");
        QMessageBox::information(this, "游戏结束", strTip, QMessageBox::Yes);
        items.clear();
        initchess();
        aiop = '4';
        // ui->lable_3->setText("white winner !!!\n\n");
    } else if (win == 3) {
        winplayer->play();
        for (int i = 0; i < items.size(); i++) {
            xitems.append(items[i]);
        }
        ui->fupan->setVisible(true);
        ui->pushButton_2->setVisible(true);
        ui->exit->setVisible(false);
        ui->tishi->setVisible(false);
        ui->huiqi->setVisible(false);
        strTip = "平局！";
        ui->lable->setText("请选择游戏模式");
        QMessageBox::information(this, "游戏结束", strTip, QMessageBox::Yes);
        items.clear();
        initchess();
        aiop = '4';
        // flagai=0;
        // ui->lable_3->setText("black winner !!!\n\n");
    }
    // printfchess();
    Fchess[Fchess_len].x = x;
    Fchess[Fchess_len].y = y;
    Fchess_len++;
    if (MainWindow::chesswin(op, x, y, 0))
        return 1;
    return 0;
}
