//
// Created by Kiyoshi on 2019-04-07.
//
#include <functional>
#include "gomoku.h"
#include "GomokuAI.h"

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

float direction_evaluate(BOARD board, const int i, const int j, const update_pos_fun_t &next,
                         const update_pos_fun_t &pre) {
    int i0 = i, j0 = j;
    pre(i0, j0);
    bool left_blocked = false;
    if (i0 < 0 || i0 > GAME_SIZE || j0 < 0 || j0 > GAME_SIZE || (board[i0][j0] == 3 - board[i][j]))
        left_blocked = true;
    bool right_blocked = false, out_of_board = false;

    i0 = i, j0 = j;
    int self = 0, blank = 0, pos;
    for (pos = 1; pos < 6; ++pos, next(i0, j0)) {
        if (i0 < 0 || j0 < 0 || i0 >= GAME_SIZE || j0 >= GAME_SIZE) {
            out_of_board = true;
            break;
        }
        if (board[i0][j0] == BLANK) {
            blank = blank * 10 + pos;
        } else if (board[i0][j0] == board[i][j]) {
            self++;
        } else if (board[i0][j0] == 3 - board[i][j]) {
            right_blocked = true;
            break;
        } else {
            continue;
        }
    }

    if (left_blocked && right_blocked)
        return 0.0;
    switch (self) {
        case 1:
            return 0;
        case 2:
            return blank == 234 ? 10 : 100;
        case 3:
            return ((blank == 45 && !left_blocked) || (blank == 35 && !left_blocked) ||
                    (blank == 25 && !left_blocked) || (blank == 4 && out_of_board)) ? 1000 : 100;
        case 4:
            return (blank == 5 && !left_blocked && !right_blocked) ? 10000 : 1000;
        case 5:
            return 100000;
        default:
            return 0.0;
    }
}



float pos_evaluate(BOARD board, int i, int j, bool is_black, uint32_t horist_val) {

    return 0.0;
}
