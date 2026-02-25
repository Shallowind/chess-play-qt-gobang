#include "Headers/quanju.h"
extern char chess[24][24];
void initchess()
{
    for (int i = 0; i < chess_n; i++) {
        for (int j = 0; j < chess_n; j++) {
            chess[i][j] = '0';
        }
    }
}
