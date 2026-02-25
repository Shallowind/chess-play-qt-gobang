#include "Headers/quanju.h"
void ChessJudge(int lian, int chessjudge[], int left, int right, char zuo, char zuo1, char zuo2, char you, char you1, char you2, char opr)
{
    if (lian >= 5) { // 下到这个地方能连起来5个
        chessjudge[0]++;
        // if (opr == 1) { score1[x][y] = 100000; X1 = x; Y1 = y; return 100000; }
        // if (opr == 2) { score2[x][y] = 100000; X2 = x; Y2 = y; return 100000; }
    }
    if (lian == 4) // 中心线4连
    {
        if (left == 0 && right == 0) // 两边断开位置均空
            chessjudge[2]++;
        else if (left == 1 && right == 1) // 两边断开位置均非空
            chessjudge[10]++; // 没有威胁
        else if (left == 0 || right == 0) // 两边断开位置只有一个空
            chessjudge[1]++; // 死四
    }
    if (lian == 3) { // 中心线3连
        if (left == 0 && right == 0) // 两边断开位置均空
        {
            if ((zuo != '0' && zuo != opr) && (you != '0' && you != opr)) {
                chessjudge[3]++;
            } else if (zuo == opr || you == opr) {
                chessjudge[1]++;

            } else if (zuo == '0' || you == '0') {
                chessjudge[4]++;
            }

        } else if (left == 1 && right == 1) // 两边断开位置均非空
        {
            chessjudge[10]++;
        } else if (left == 0 || right == 0) // 两边断开位置只有一个空
        {
            if (left == 1) { // 左边被对方堵住
                if (you != '0' && you != opr) {
                    chessjudge[10]++;
                }
                if (you == '0') {
                    chessjudge[3]++;
                }
                if (you == opr) {
                    chessjudge[1]++;
                }
            }
            if (right == 1) { // 右边被对方堵住
                if (zuo != '0' && zuo != opr) {
                    chessjudge[10]++;
                }
                if (zuo == '0') {
                    chessjudge[3]++;
                }
                if (zuo == opr) {
                    chessjudge[1]++;
                }
            }
        }
    }
    int JianCha = 0;
    if (lian == 2) {
        if (left == 0 && right == 0) { // 两边断开位置均空
            if ((you == '0' && you1 == opr) || (zuo == '0' && zuo1 == opr)) {
                chessjudge[3]++;
                JianCha = 1;
            } else if (zuo == '0' && you == '0') {
                chessjudge[7]++;
                JianCha = 1;
            }
            if ((you == opr && you1 != opr && you1 != '0') || (zuo == opr && zuo1 != opr && zuo1 != '0')) {
                chessjudge[3]++;
                JianCha = 1;
            }
            if ((you == opr && you1 == opr) || (zuo == opr && zuo1 == opr)) {
                chessjudge[5]++;
                JianCha = 1;
            }
            if ((you == opr && you1 == '0') || (zuo == opr && zuo1 == '0')) {
                chessjudge[6]++;
                JianCha = 1;
            }
            if (JianCha == 0) {
                chessjudge[10]++;
            }
        } else if (left == 1 && right == 1) // 两边断开位置均非空
        {
            chessjudge[10]++;
        } else if (left == 0 || right == 0) // 两边断开位置只有一个空
        {
            if (left == 1) { // 左边被对方堵住
                if ((you != opr && you != '0') || (you1 != '0' && you1 != opr)) { // 只要有对方的一个棋子
                    chessjudge[10]++; // 没有威胁
                } else if (you == '0' && you1 == '0') { // 均空
                    chessjudge[9]++; // 死2
                } else if (you == opr && you1 == opr) { // 均为自己的棋子
                    chessjudge[1]++; // 死4
                } else if (you == opr || you1 == opr) { // 只有一个自己的棋子
                    chessjudge[3]++; // 死3
                }
            }
            if (right == 1) { // 右边被对方堵住
                if ((zuo != opr && zuo != '0') || (zuo1 != '0' && zuo1 != opr)) { // 只要有对方的一个棋子
                    chessjudge[10]++; // 没有威胁
                } else if (zuo == '0' && zuo1 == '0') { // 均空
                    chessjudge[9]++; // 死2
                } else if (zuo == opr && zuo1 == opr) { // 均为自己的棋子
                    chessjudge[1]++;
                    ; // 死4
                } else if (zuo == opr || zuo1 == opr) { // 只有一个自己的棋子
                    chessjudge[3]++; // 死3
                }
            }
        }
    }
    if (lian == 1) { // 中心线1连
        JianCha = 0;
        if (left == 0 && zuo == opr && zuo1 == opr && zuo2 == opr) {
            chessjudge[5]++;
            JianCha = 1;
        }
        if (right == 0 && you == opr && you1 == opr && you2 == opr) {
            chessjudge[5]++;
            JianCha = 1;
        }
        if (left == 0 && zuo == opr && zuo1 == opr && zuo2 == '0' && right == 0) {
            chessjudge[6]++;
            JianCha = 1;
        }
        if (right == 0 && you == opr && you1 == opr && you2 == '0' && left == 0) {
            chessjudge[6]++;
            JianCha = 1;
        }
        if (left == 0 && zuo == opr && zuo1 == opr && (zuo2 != 0 && zuo2 != opr) && right == 0) {
            chessjudge[3]++;
            JianCha = 1;
        }
        if (right == 0 && you == opr && you1 == opr && (you2 != 0 && you2 != opr) && left == 0) {
            chessjudge[3]++;
            JianCha = 1;
        }
        if (left == 0 && zuo == '0' && zuo1 == opr && zuo2 == opr) {
            chessjudge[3]++;
            JianCha = 1;
        }
        if (right == 0 && you == '0' && you1 == opr && you2 == opr) {
            chessjudge[3]++;
            JianCha = 1;
        }
        if (left == 0 && zuo == opr && zuo1 == '0' && zuo2 == opr) {
            chessjudge[3]++;
            JianCha = 1;
        }
        if (right == 0 && you == opr && you1 == '0' && you2 == opr) {
            chessjudge[3]++;
            JianCha = 1;
        }
        if (left == 0 && zuo == opr && zuo1 == '0' && zuo2 == '0' && right == 0) {
            chessjudge[8]++;
            JianCha = 1;
        }
        if (right == 0 && you == opr && you1 == '0' && you2 == '0' && left == 0) {
            chessjudge[8]++;
            JianCha = 1;
        }
        if (left == 0 && zuo == '0' && zuo1 == opr && zuo2 == '0' && right == 0) {
            chessjudge[8]++;
            JianCha = 1;
        }
        if (right == 0 && you == '0' && you1 == opr && you2 == '0' && left == 0) {
            chessjudge[8]++;
            JianCha = 1;
        }
        if (JianCha == 0)
            chessjudge[10]++;
    }
}
int ChessScore(int lian, int x, int y, char opr, int mode)
{
    int sum = 0;
    int max = 0;

    //	int yingwu = 0, sisi = 0, huosi = 0, sisan = 0, huosan = 0, lowsisi = 0, tiaosan = 0, huoer = 0, lowhuoer = 0, sier = 0, noth = 0;

    int Mode[4][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
    char zuo = '8', you = '8';
    char zuo1 = '8', you1 = '8';
    char zuo2 = '8', you2 = '8';
    int left = 1, right = 1;
    if (mode == 1) {
        for (int k = 1; k <= 4; k++) { // 横着判断
            if (y + k == chess_n) {
                you = '8';
                break;
            }
            if (chess[x][y + k] != opr) {
                if (chess[x][y + k] == '0') {
                    right = 0;
                }
                if (y + k + 1 == chess_n)
                    you = '8';
                else
                    you = chess[x][y + k + 1];
                if (y + k + 2 == chess_n)
                    you1 = '8';
                else
                    you1 = chess[x][y + k + 2];
                if (y + k + 3 == chess_n)
                    you2 = '8';
                else
                    you2 = chess[x][y + k + 3];
                break;
            }
        }
        for (int k = 1; k <= 4; k++) {
            if (y - k == 0) {
                zuo = '8';
                break;
            }
            if (chess[x][y - k] != opr) {
                if (chess[x][y - k] == '0') {
                    left = 0;
                }
                if (y - k - 1 == 0)
                    zuo = '8';
                else
                    zuo = chess[x][y - k - 1];
                if (y - k - 2 == 0)
                    zuo1 = '8';
                else
                    zuo1 = chess[x][y - k - 2];
                if (y - k - 3 == 0)
                    zuo2 = '8';
                else
                    zuo2 = chess[x][y - k - 3];
                break;
            }
        }

        ChessJudge(lian, chessjudge, left, right, zuo, zuo1, zuo2, you, you1, you2, opr);
        zuo = '8';
        you = '8';
        zuo1 = '8';
        you1 = '8';
        zuo2 = '8';
        you2 = '8';
        left = 1;
        right = 1;
    }
    if (mode == 2) {
        // 竖着判断
        for (int k = 1; k <= 4; k++) {
            if (x + k == chess_n) {
                you = '8';
                break;
            }
            if (chess[x + k][y] != opr) {
                if (chess[x + k][y] == '0') {
                    right = 0;
                }
                if (x + k + 1 == chess_n)
                    you = '8';
                else
                    you = chess[x + k + 1][y];
                if (x + k + 2 == chess_n)
                    you1 = '8';
                else
                    you1 = chess[x + k + 2][y];
                if (x + k + 3 == chess_n)
                    you2 = '8';
                else
                    you2 = chess[x + k + 3][y];
                break;
            }
        }
        for (int k = 1; k <= 4; k++) {
            if (x - k == 0) {
                zuo = '8';
                break;
            }
            if (chess[x - k][y] != opr) {
                if (chess[x - k][y] == '0') {
                    left = 0;
                }
                if (x - k - 1 == 0)
                    zuo = '8';
                else
                    zuo = chess[x - k - 1][y];
                if (x - k - 2 == 0)
                    zuo1 = '8';
                else
                    zuo1 = chess[x - k - 2][y];
                if (x - k - 3 == 0)
                    zuo2 = '8';
                else
                    zuo2 = chess[x - k - 3][y];
                break;
            }
        }
        ChessJudge(lian, chessjudge, left, right, zuo, zuo1, zuo2, you, you1, you2, opr);
        // 左上右下判断
        zuo = '8';
        you = '8';
        zuo1 = '8';
        you1 = '8';
        zuo2 = '8';
        you2 = '8';
        left = 1;
        right = 1;
    }
    if (mode == 3) {
        for (int k = 1; k <= 4; k++) {
            if (x + k == chess_n || y + k == chess_n) {
                you = '8';
                break;
            }
            if (chess[x + k][y + k] != opr) {
                if (chess[x + k][y + k] == '0') {
                    right = 0;
                }
                if (x + k + 1 == chess_n || y + k + 1 == chess_n)
                    you = '8';
                else
                    you = chess[x + k + 1][y + k + 1];
                if (x + k + 2 == chess_n || y + k + 2 == chess_n)
                    you1 = '8';
                else
                    you1 = chess[x + k + 2][y + k + 2];
                if (x + k + 3 == chess_n || y + k + 3 == chess_n)
                    you2 = '8';
                else
                    you2 = chess[x + k + 3][y + k + 3];
                break;
            }
        }
        for (int k = 1; k <= 4; k++) {
            if (x - k == chess_n || y - k == chess_n) {
                zuo = '8';
                break;
            }
            if (chess[x - k][y - k] != opr) {
                if (chess[x - k][y - k] == '0') {
                    left = 0;
                }
                if (x - k - 1 == chess_n || y - k - 1 == chess_n)
                    zuo = '8';
                else
                    zuo = chess[x - k - 1][y - k - 1];
                if (x - k - 2 == chess_n || y - k - 2 == chess_n)
                    zuo1 = '8';
                else
                    zuo1 = chess[x - k - 2][y - k - 2];
                if (x - k - 3 == chess_n || y - k - 3 == chess_n)
                    zuo2 = '8';
                else
                    zuo2 = chess[x - k - 3][y - k - 3];
                break;
            }
        }
        ChessJudge(lian, chessjudge, left, right, zuo, zuo1, zuo2, you, you1, you2, opr);
        zuo = '8';
        you = '8';
        zuo1 = '8';
        you1 = '8';
        zuo2 = '8';
        you2 = '8';
        left = 1;
        right = 1;
    }
    if (mode == 4) {
        for (int k = 1; k <= 4; k++) {
            if (x + k == chess_n || y - k == chess_n) {
                you = '8';
                break;
            }
            if (chess[x + k][y - k] != opr) {
                if (chess[x + k][y - k] == '0') {
                    right = 0;
                }
                if (x + k + 1 == chess_n || y - k - 1 == chess_n)
                    you = '8';
                else
                    you = chess[x + k + 1][y - k - 1];
                if (x + k + 2 == chess_n || y - k - 2 == chess_n)
                    you1 = '8';
                else
                    you1 = chess[x + k + 2][y - k - 2];
                if (x + k + 3 == chess_n || y - k - 3 == chess_n)
                    you2 = '8';
                else
                    you2 = chess[x + k + 3][y - k - 3];
                break;
            }
        }
        for (int k = 1; k <= 4; k++) {
            if (x - k == chess_n || y + k == chess_n) {
                zuo = '8';
                break;
            }
            if (chess[x - k][y + k] != opr) {
                if (chess[x - k][y + k] == '0') {
                    left = 0;
                }
                if (x - k - 1 == chess_n || y + k + 1 == chess_n)
                    zuo = '8';
                else
                    zuo = chess[x - k - 1][y + k + 1];
                if (x - k - 2 == chess_n || y + k + 2 == chess_n)
                    zuo1 = '8';
                else
                    zuo1 = chess[x - k - 2][y + k + 2];
                if (x - k - 3 == chess_n || y + k + 3 == chess_n)
                    zuo2 = '8';
                else
                    zuo2 = chess[x - k - 3][y + k + 3];
                break;
            }
        }
        ChessJudge(lian, chessjudge, left, right, zuo, zuo1, zuo2, you, you1, you2, opr);
    }
    int JianCha = 0;
    if (chessjudge[0] >= 1 && JianCha == 0) {
        /*        if(opr=='1'&&lian>5){
                    max=-1;
                    score1[x][y]=-1;
                }
                else*/
        max = 14;
        JianCha = 1;
    } else if (JianCha == 0 && (chessjudge[2] >= 1 || chessjudge[1] >= 2 || (chessjudge[1] >= 1 && chessjudge[4] >= 1))) {
        /*        if(opr=='1'&&chessjudge[1]>=2){
                    max=-1;
                    score1[x][y]=-1;
                }
                else*/
        max = 13;
        JianCha = 1;
    } // 活4 双死4 死4活3
    else if (JianCha == 0 && (chessjudge[4] + chessjudge[6] >= 2)) {
        /*        if(opr=='1'){
                    max=-1;
                    score1[x][y]=-1;
                }
                else*/
        max = 12;
        JianCha = 1;
    } // 双活3
    else if (JianCha == 0 && chessjudge[3] >= 1 && chessjudge[4] >= 1) {
        max = 11;
        JianCha = 1;
    } // 死3高级活3
    else if (JianCha == 0 && chessjudge[1] >= 1) {
        max = 10;
        JianCha = 1;
    } // 高级死4
    else if (JianCha == 0 && chessjudge[5] >= 1) {
        max = 9;
        JianCha = 1;
    } // 低级死4
    else if (JianCha == 0 && chessjudge[4] >= 1) {
        max = 8;
        JianCha = 1;
    } // 单活3
    else if (JianCha == 0 && chessjudge[6] >= 1) {
        max = 7;
        JianCha = 1;
    } // 跳活3
    else if (JianCha == 0 && chessjudge[7] >= 2) {
        max = 6;
        JianCha = 1;
    } // 双活2
    else if (JianCha == 0 && chessjudge[7] >= 1) {
        max = 5;
        JianCha = 1;
    } // 活2
    else if (JianCha == 0 && chessjudge[8] >= 1) {
        max = 4;
        JianCha = 1;
    } // 低级活2
    else if (JianCha == 0 && chessjudge[3] >= 1) {
        max = 3;
        JianCha = 1;
    } // 死3
    else if (JianCha == 0 && chessjudge[9] >= 1) {
        max = 2;
        JianCha = 1;
    } // 死2
    if (JianCha == 0)
        max = 1;
    if (opr == '1') {
        if (max > score1[x][y] && score1[x][y] != -1)
            score1[x][y] = max;
        X1 = x;
        Y1 = y;
        return max;
    }
    if (opr == '2') {
        if (max > score1[x][y] && score1[x][y] != -1)
            score1[x][y] = max;
        X2 = x;
        Y2 = y;
        return max;
    }
}
