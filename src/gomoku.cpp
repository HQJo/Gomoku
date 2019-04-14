//
// Created by Kiyoshi on 2019-04-07.
//
#include <functional>
#include "gomoku.h"
#include "GomokuAI.h"

namespace GOMOKUZHQ {
    void print_board(const board_t &board) {
        auto size = board.size();
        printf("  | ");
        for (auto i = 1; i <= size; ++i)
            printf("%2d| ", i);
        printf("\n");
        for (auto i = 0; i < size + 1; ++i)
            printf("----");
        printf("\n");

        for (auto i = 0; i < size; ++i) {
            printf("%2d| ", i + 1);
            for (auto j = 0; j < size; ++j) {
                if (board[i][j] == BLACK)
                    printf("* | ");
                else if (board[i][j] == WHITE)
                    printf("o | ");
                else
                    printf("  | ");
            }
            printf("\n");
            for (auto k = 0; k < size + 1; ++k)
                printf("----");
            printf("\n");
        }
    }

};

