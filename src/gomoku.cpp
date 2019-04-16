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
        for (unsigned i = 1; i <= size; ++i)
            printf("%2d| ", i);
        printf("\n");
        for (unsigned i = 0; i < size + 1; ++i)
            printf("----");
        printf("\n");

        for (unsigned i = 0; i < size; ++i) {
            printf("%2d| ", i + 1);
            for (unsigned j = 0; j < size; ++j) {
                if (board[i][j] == BLACK)
                    printf("* | ");
                else if (board[i][j] == WHITE)
                    printf("o | ");
                else
                    printf("  | ");
            }
            printf("\n");
            for (unsigned k = 0; k < size + 1; ++k)
                printf("----");
            printf("\n");
        }
    }

    int direction_count(const board_t &board, int x, int y, update_pos_fun_t &next) {
        auto size = board.size();

        int i0 = x, j0 = y, cnt = 0;
        while (i0 >= 0 && j0 >= 0 && i0 < size && j0 < size && board[i0][j0] == board[x][y]) {
            ++cnt;
            next(i0, j0);
        }
        return cnt;
    }

    std::pair<bool, bool> check_game_end(const board_t &board) {
        auto size = board.size();
        update_pos_fun_t directions[4] = {
                [](int &x, int &y) { ++y; },
                [](int &x, int &y) { ++x; },
                [](int &x, int &y) { ++x, ++y; },
                [](int &x, int &y) { ++x, --y; }
        };
        for (unsigned i = 0;i < size;++i) {
            for (unsigned j = 0;j < size;++j) {
                for (auto &direction : directions) {
                    if (direction_count(board, i, j, direction) >= 5) {
                        return std::make_pair(true, board[i][j] == BLACK);
                    }
                }
            }
        }
        return std::make_pair(false, false);
    }
};

