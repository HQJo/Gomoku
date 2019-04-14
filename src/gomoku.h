//
// Created by Kiyoshi on 2019-04-01.
//

#ifndef GOMOKU_GOMOKU_H
#define GOMOKU_GOMOKU_H

#include <cstdio>
#include <functional>

namespace GOMOKUZHQ {
    const int BLANK = 0, BLACK = 1, WHITE = 2;
    using board_t = std::vector<std::vector<int>>;

    void print_board(const board_t &board);
}

#endif //GOMOKU_GOMOKU_H
