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
    using update_pos_fun_t = std::function<void(int &, int &)>;

    void print_board(const board_t &board);
    int direction_count(const board_t &board, int x, int y, update_pos_fun_t &next);
    std::pair<bool, bool> check_game_end(const board_t &board);
}

#endif //GOMOKU_GOMOKU_H
