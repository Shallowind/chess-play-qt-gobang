#include"quanju.h"
int huiqi() {
    int op;
    int ans = 5;
    while (ans >= 0) {
        printf("悔棋倒计时 ：%d\r", ans);
        Sleep(1000);
        ans--;
        if (_kbhit()) {
            op = _getch();
            if (op == 13) return 0;
            else return 1;
        }
    }
    return 0;
}
