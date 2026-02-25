#include "Headers/quanju.h"
void eight_direction(int chess_i, int chess_j, int sum[], char chess_flag)
{
    int i, j, k, n = chess_n, num;
    int a[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }, b[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    for (k = 0; k < 8; k++) {
        num = 0, i = chess_i, j = chess_j;
        while (i + a[k] >= 0 && i + a[k] < n && j + b[k] >= 0 && j + b[k] < n && chess_jin[i + a[k]][j + b[k]] == chess_flag) {
            num++;
            i += a[k];
            j += b[k];
        }
        sum[k] = num;
    }
}
