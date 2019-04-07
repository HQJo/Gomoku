//
// Created by Kiyoshi on 2019-04-07.
//
#include "gomoku.h"
#include <random>

void init_horist(uint32_t horist[][GAME_SIZE][2]) {
    std::random_device r;
    std::seed_seq seed{r()};
    std::independent_bits_engine<std::mt19937, 32, uint32_t> engine(seed);

    for (int i = 0;i < GAME_SIZE;++i) {
        for (int j = 0;j < GAME_SIZE;++j) {
            for (int k = 0;k < 2;++k) {
                horist[i][j][k] = engine();
            }
        }
    }
}

uint32_t _calc_horist(BOARD board, uint32_t horist[][GAME_SIZE][2]) {
    uint32_t h = 0;
    for (int i = 0;i < GAME_SIZE;++i) {
        for (int j = 0;j < GAME_SIZE;++j) {
            if (board[i][j] != BLANK) {
                h ^= horist[i][j][board[i][j]-1];
            }
        }
    }
    return h;
}
