#include"quanju.h"
void printfchess() {
    //┌ ┬ ┐├ ┼ ┤└ ┴ ┘│─●○
    //system("cls");
    int i, j;
    printf("\n  ");
    for (j = 0; j < chess_n; j++) printf(j < 10 ? "%d " : "%d", j);
    printf("\n");
    for (i = 0; i < chess_n; i++) {
        printf("%2d", i);
        for (j = 0; j < chess_n; j++) {
            if (i == 0) {
                if (j == 0) {
                    if (chess[i][j] == '0') printf("┌ ");
                    else if (chess[i][j] == '1') printf("○");
                    else if (chess[i][j] == '2') printf("●");
                }
                else if (j == chess_n - 1) {
                    if (chess[i][j] == '0') printf("┐ ");
                    else if (chess[i][j] == '1') printf("○");
                    else if (chess[i][j] == '2') printf("●");
                }
                else {
                    if (chess[i][j] == '0') printf("┬ ");
                    else if (chess[i][j] == '1') printf("○");
                    else if (chess[i][j] == '2') printf("●");
                }
            }
            else if (i == chess_n - 1) {
                if (j == 0) {
                    if (chess[i][j] == '0') printf("└ ");
                    else if (chess[i][j] == '1') printf("○");
                    else if (chess[i][j] == '2') printf("●");
                }
                else if (j == chess_n - 1) {
                    if (chess[i][j] == '0') printf("┘ ");
                    else if (chess[i][j] == '1') printf("○");
                    else if (chess[i][j] == '2') printf("●");
                }
                else {
                    if (chess[i][j] == '0') printf("┴ ");
                    else if (chess[i][j] == '1') printf("○");
                    else if (chess[i][j] == '2') printf("●");
                }
            }
            else {
                if (j == 0) {
                    if (chess[i][j] == '0') printf("├ ");
                    else if (chess[i][j] == '1') printf("○");
                    else if (chess[i][j] == '2') printf("●");
                }
                else if (j == chess_n - 1) {
                    if (chess[i][j] == '0') printf("┤ ");
                    else if (chess[i][j] == '1') printf("○");
                    else if (chess[i][j] == '2') printf("●");
                }
                else {
                    if (chess[i][j] == '0') printf("┼ ");
                    else if (chess[i][j] == '1') printf("○");
                    else if (chess[i][j] == '2') printf("●");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}
