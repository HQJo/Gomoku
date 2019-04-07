//
// Created by Kiyoshi on 2019-04-07.
//
#include "gomoku.h"

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
