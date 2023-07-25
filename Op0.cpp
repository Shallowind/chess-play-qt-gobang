#include"quanju.h"
void chessop0() {
    int i;
    for (i = 0; i < Fchess_len; i++) {
        chess[Fchess[i].x][Fchess[i].y] = i & 1 ? '2' : '1';
        printfchess();
        cout << "第" << i + 1 << "步" << endl;
        system("pause");
    }
}
