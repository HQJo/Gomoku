//
// Created by Kiyoshi on 2019-04-01.
//

#ifndef GOMOKU_GOMOKU_H
#define GOMOKU_GOMOKU_H

const int GAME_SIZE = 15;
const int BLANK = 0, BLACK = 1, WHITE = 2;
using BOARD = int[GAME_SIZE][GAME_SIZE];

void print_board(BOARD board) {
    printf("  | ");
    for (int i = 1; i <= GAME_SIZE; ++i)
        printf("%2d| ", i);
    printf("\n");
    for (int i = 0; i < GAME_SIZE + 1; ++i)
        printf("----");
    printf("\n");

    for (int i = 0; i < GAME_SIZE; ++i) {
        printf("%2d| ", i + 1);
        for (int j = 0; j < GAME_SIZE; ++j) {
            if (board[i][j] == BLACK)
                printf("* | ");
            else if (board[i][j] == WHITE)
                printf("o | ");
            else
                printf("  | ");
        }
        printf("\n");
        for (int k = 0; k < GAME_SIZE + 1; ++k)
            printf("----");
        printf("\n");
    }
}

#endif //GOMOKU_GOMOKU_H
