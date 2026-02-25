#include "Headers/quanju.h"
#include <QDebug>
int huosi(int chess_i, int chess_j, int chess_k)
{
    //    qDebug() << chess_i << " " << chess_j << " 方向 " << chess_k << "活四禁手判断" << endl;
    int i, j, n = chess_n, flag = 0, k = chess_k;
    chess_jin[chess_i][chess_j] = '1';
    int a[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }, b[8] = { -1, 0, 1, -1, 1, -1, 0, 1 }, sum[8];
    eight_direction(chess_i, chess_j, sum, '1');
    for (i = 0; i < 8; i++) {
        qDebug() << sum[i] << " ";
    }
    if (sum[k] + sum[7 - k] + 1 == 4) {
        for (int q = 0; q < 2; q++) {
            if (q == 0)
                k = chess_k;
            else
                k = 7 - chess_k;
            i = chess_i + a[k] * (sum[k] + 1);
            j = chess_j + b[k] * (sum[k] + 1);
            if (i >= 0 && i < n && j >= 0 && j < n && chess_jin[i][j] == '0' && jinshou(i, j) == 0)
                flag++;
        }
        if (flag == 2) {
            chess_jin[chess_i][chess_j] = '0';
            return 1;
        }
    }
    chess_jin[chess_i][chess_j] = '0';
    return 0;
}
int chongsi(int chess_i, int chess_j, int chess_k)
{
    //    qDebug() << chess_i << " " << chess_j << " 方向 " << chess_k << "冲四禁手判断" << endl;
    int a[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }, b[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    chess_jin[chess_i][chess_j] = '1';
    int i, j, p, q, sum, n = chess_n, k = chess_k;
    for (p = 0; p < 5; p++) {
        i = chess_i + p * a[k], j = chess_j + p * b[k], sum = 0;
        if (!(i >= 0 && i < n && j >= 0 && j < n))
            break;
        for (q = 0; q < 5; q++) {
            if (chess_jin[i][j] == '1')
                sum++;
            else if (chess_jin[i][j] == '2')
                break;
            i += a[7 - k], j += b[7 - k];
            if (!(i >= 0 && i < n && j >= 0 && j < n))
                break;
        }
        if (sum == 4) {
            i = chess_i + p * a[k], j = chess_j + p * b[k];
            if (!(i >= 0 && i < n && j >= 0 && j < n))
                break;
            for (q = 0; q < 5; q++) {
                if (chess_jin[i][j] == '0') {
                    if (jinshou(i, j) == 0) {
                        chess_jin[chess_i][chess_j] = '0';
                        return 1;
                    } else
                        break;
                }
                i += a[7 - k], j += b[7 - k];
                if (!(i >= 0 && i < n && j >= 0 && j < n))
                    break;
            }
        }
    }
    chess_jin[chess_i][chess_j] = '0';
    return 0;
}
int huosan(int chess_i, int chess_j, int chess_k, int sum[])
{
    //    qDebug() << chess_i << " " << chess_j << " 方向 " << chess_k << "活三禁手判断" << endl;
    int i, j, n = chess_n, k = chess_k;
    int a[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }, b[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    chess_jin[chess_i][chess_j] = '1';
    int p, q;
    int num = sum[chess_k] + sum[7 - chess_k] + 1;
    if (num == 3) {
        for (q = 0; q < 2; q++) {
            if (q == 0)
                k = chess_k;
            else
                k = 7 - chess_k;
            i = chess_i + a[k] * (sum[k] + 1);
            j = chess_j + b[k] * (sum[k] + 1);
            if (!(i >= 0 && i < n && j >= 0 && j < n))
                break;
            if (chess_jin[i][j] == '0' && jinshou(i, j) == 0 && huosi(i, j, chess_k)) {
                chess_jin[chess_i][chess_j] = '0';
                return 3;
            }
        }
    } else if (num == 1) {
        for (q = 0; q < 2; q++) {
            if (q == 0)
                k = chess_k;
            else
                k = 7 - chess_k;
            for (p = 3; p >= 1; p--) {
                i = chess_i + p * a[k], j = chess_j + p * b[k];
                if (!(i >= 0 && i < n && j >= 0 && j < n))
                    break;
                if (p == 1) {
                    if (chess_jin[i][j] == '0' && jinshou(i, j) == 0 && huosi(i, j, chess_k)) {
                        chess_jin[chess_i][chess_j] = '0';
                        return 1;
                    }
                } else {
                    if (chess_jin[i][j] != '1')
                        break;
                }
            }
        }
    } else if (num == 2) {
        for (q = 0; q < 2; q++) {
            if (q == 0)
                k = chess_k;
            else
                k = 7 - chess_k;
            int ki = chess_i + sum[k] * a[k], kj = chess_j + sum[k] * b[k];
            int flag = 1;
            for (p = 2; p >= 1; p--) {
                i = ki + p * a[k], j = kj + p * b[k];
                if (!(i >= 0 && i < n && j >= 0 && j < n)) {
                    flag = 0;
                    break;
                }
                if (p == 2) {
                    if (chess_jin[i][j] != '1') {
                        flag = 0;
                        break;
                    }
                } else {
                    if (chess_jin[i][j] != '0' || jinshou(i, j) == 1 || huosi(i, j, chess_k) == 0) {
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag) {
                chess_jin[chess_i][chess_j] = '0';
                return 2;
            }
        }
    }
    chess_jin[chess_i][chess_j] = '0';
    return 0;
}
int si_si(int chess_i, int chess_j)
{
    //    qDebug() << chess_i << " " << chess_j << "四四禁手判断" << endl;
    int i = chess_i, j = chess_j, k, flag = 0;
    for (k = 0; k < 4; k++) {
        if (chongsi(i, j, k)) {
            //            qDebug() << chess_i << " " << chess_j << "四四禁手" << endl;
            flag++;
        }
        if (flag == 2)
            return 1;
    }
    return 0;
}
int san_san(int chess_i, int chess_j, int sum[])
{
    //    qDebug() << chess_i << " " << chess_j << "三三禁手判断" << endl;
    int i = chess_i, j = chess_j, k, flag = 0;
    for (k = 0; k < 4; k++) {
        if (huosan(i, j, k, sum)) {
            //            qDebug() << chess_i << " " << chess_j << "三三禁手" << endl;
            flag++;
        }
        if (flag == 2)
            return 1;
    }
    return 0;
}
int jinshou(int chess_i, int chess_j)
{
    int k, Max = 0;
    int a[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }, b[8] = { -1, 0, 1, -1, 1, -1, 0, 1 }, sum[8] = { 0 };
    eight_direction(chess_i, chess_j, sum, '1');
    //    qDebug() << chess_i << " " << chess_j << "禁手判断" << endl;
    for (k = 0; k < 8; k++) {
        qDebug() << sum[k] << " ";
    }
    cout << endl;
    for (k = 0; k < 4; k++) {
        if (sum[k] + sum[7 - k] + 1 == 5)
            return 0;
        if (sum[k] + sum[7 - k] + 1 > Max)
            Max = sum[k] + sum[7 - k] + 1;
    }
    if (Max > 5) {
        //        qDebug() << chess_i << " " << chess_j << "长连禁手" << endl;
        return 1;
    }
    if (si_si(chess_i, chess_j)) {
        //        qDebug() << chess_i << " " << chess_j << "四四禁手" << endl;
        return 2;
    }
    if (san_san(chess_i, chess_j, sum)) {
        //        qDebug() << chess_i << " " << chess_j << "三三禁手" << endl;
        return 3;
    }
    //    qDebug() << chess_i << " " << chess_j << "不是禁手" << endl;
    return 0;
}
