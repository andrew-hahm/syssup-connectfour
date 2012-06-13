/*
 * connectfour.c
 *
 *  Created on: Jun 13, 2012
 *      Author: andhah
 */

#include <stdio.h>
#include <stdlib.h>

int checkwin();
int getcoord();
int placeitem();
void printmap();
/*
int computer_ai();
int human_predictor();
*/
int checkwin(int board[6][7]) {
    int x, y;

    for (y = 0; y < 7; y++) {
        for (x = 0; x < 3; x++) {
            if (board[x][y] == 1 && board[x+1][y] == 1 && board[x+2][y] == 1 && board[x+3][y] == 1) {
                return 0;
            } else if (board[x][y] == 2 && board[x+1][y] == 2 && board[x+2][y] == 2 && board[x+3][y] == 2) {
                return 1;
            }
        }
    }

    for (x = 0; x < 6; x++) {
        for (y = 0; y < 4; y++) {
            if (board[x][y] == 1 && board[x][y+1] == 1 && board[x][y+2] == 1 && board[x][y+3] == 1) {
                return 0;
            } else if (board[x][y] == 2 && board[x][y+1] == 2 && board[x][y+2] == 2 && board[x][y+3] == 2) {
                return 1;
            }
        }
    }

    for (x = 0; x < 3; x++) {
        for (y = 0; y < 4; y++) {
            if (board[x][y] == 1 && board[x+1][y+1] == 1 && board[x+2][y+2] == 1 && board[x+3][y+3] == 1) {
                return 0;
            } else if (board[x][y] == 2 && board[x+1][y+1] == 2 && board[x+2][y+2] == 2 && board[x+3][y+3] == 2) {
                return 1;
            }
        }
    }

    for (x = 0; x < 3; x++) {
        for (y = 6; y > 2; y--) {
            if (board[x][y] == 1 && board[x+1][y-1] == 1 && board[x+2][y-2] == 1 && board[x+3][y-3] == 1) {
                return 0;
            } else if (board[x][y] == 2 && board[x+1][y-1] == 2 && board[x+2][y-2] == 2 && board[x+3][y-3] == 2) {
                return 1;
            }
        }
    }
    return -1;
}

int getcoord() {
    int x = -1;

    do {
        printf("Column number: ");
        scanf("%d", &x);
        if (x > 6 || x < 1) {
            printf("Error: please enter a number between 1 and 6 inclusive.\n");
        }
    } while (x > 6 || x < 1);

    return x;
}

int placeitem(int playernum, int x, int board[6][7], int outputsuppress, int actualplacement) {
    int y;

    for (y = 0; y < 7; y++) {
        if (board[x][y] == 0) {
            board[x][y] = playernum + 1;
            return 0;
        }
    }
    if (outputsuppress == 0) {
        printf("This column is full!\n");
    }
    return 1;
}

void printmap(int board[6][7]) {
    int x, y;

    for (x = 6; x >= 0; x--) {
        printf("-------------------------\n");
        for (y = 0; y < 6; y++) {
            printf("| ");
            if (board[y][x] == 1) {
                printf("O ");
            } else if (board[y][x] == 2) {
                printf("X ");
            } else {
                printf("  ");
            }
        }
        printf("|\n");
    }
    printf("-------------------------\n\n");
}
/*
int computer_ai(int board[3][3], int level, int moves) {
    int wincheck, x, y, placesuccess, noderootmax, bestnodex, bestnodey, bestnoderootmax, numvalues=0, p, q;
    int boardcopy[3][3] = { { 0 } };
    int values[3][9] = { { 0 } };

    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            for (p = 0; p < 3; p++) {
                for (q = 0; q < 3; q++) {
                    boardcopy[p][q] = board[p][q];
                }
            }
            placesuccess = placeitem(1, x, y, boardcopy, 1, 0);
            if (placesuccess == 0) {
                wincheck = checkwin(boardcopy);
                if (wincheck == 1 && level == 1){
                    placeitem(1, x, y, board, 1, 1);
                    return 0;
                } else if (wincheck == 1 && level > 1) {
                    return 1;
                } else if (wincheck == -1) {
                    noderootmax = 0;
                    if (moves + 1 < 9) {
                        noderootmax = human_predictor(boardcopy, level + 1, moves + 1);
                    }
                    if (moves + 1 == 9) {
                        return 0;
                    }
                    if (noderootmax > -100) {
                        values[0][numvalues] = noderootmax;
                        values[1][numvalues] = x;
                        values[2][numvalues] = y;
                        numvalues++;
                    }
                }
            }
        }
    }

    bestnoderootmax = values[0][0];
    bestnodex = values[1][0];
    bestnodey = values[2][0];
    for (x = 0; x < numvalues-1; x++) {
        if (values[0][x+1] > values[0][x]) {
            bestnoderootmax = values[0][x+1];
            bestnodex = values[1][x+1];
            bestnodey = values[2][x+1];
        }
    }
    if (level == 1) {
        return placeitem(1, bestnodex, bestnodey, board, 1, 1);
    } else {
        return bestnoderootmax;
    }
}

int human_predictor(int board[3][3], int level, int moves) {
    int wincheck, x, y, placesuccess, noderootmin, bestnoderootmin, numvalues=0, p, q;
    int boardcopy[3][3] = { { 0 } };
    int values[3][9] = { { 0 } };

    for (x = 0; x < 3; x++) {
        for (y = 0; y < 3; y++) {
            for (p = 0; p < 3; p++) {
                for (q = 0; q < 3; q++) {
                    boardcopy[p][q] = board[p][q];
                }
            }

            placesuccess = placeitem(0, x, y, boardcopy, 1, 0);

            if (placesuccess == 0) {
                wincheck = checkwin(boardcopy);
                if (wincheck == 0) {
                    return -1;
                } else if (wincheck == -1) {
                    if (moves + 1 == 9) {
                        return 0;
                    }
                    noderootmin = 0;
                    noderootmin = computer_ai(boardcopy, level + 1, moves + 1);
                    if (noderootmin < 100) {
                        values[0][numvalues] = noderootmin;
                        values[1][numvalues] = x;
                        values[2][numvalues] = y;
                        numvalues++;
                    }
                }
            }
        }
    }

    bestnoderootmin = values[0][0];
    for (x = 0; x < numvalues-1; x++) {
        if (values[0][x+1] < values[0][x]) {
            bestnoderootmin = values[0][x+1];
        }
    }
    return bestnoderootmin;
}
*/
int main() {
    int player = 0, moves = 0, end = -1, x, successplace;
    int board[6][7] = { { 0 } };

    printmap(board);

    do {
        successplace = 1;

        if (player == 0) {
            printf("Player O's turn\n");
        } else {
            printf("Player X's turn\n");
        }
/*
        if (player == 1) {
            x = computer_ai(board, 1, moves);
        } else {
*/
        do {
            x = getcoord();
            successplace = placeitem(player, x-1, board, 0, 1);
        } while (successplace == 1);

        printmap(board);

        end = checkwin(board);

        moves++;
        player = (player + 1) % 2;
    } while (end == -1 && moves < 42);

    if (end == -1) {
        printf("Draw\n");
    } else {
        printf("Player %d wins!\n", end + 1);
    }

    return EXIT_SUCCESS;
}
