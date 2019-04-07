//
// Created by Kiyoshi on 2019-04-07.
//

#ifndef GOMOKU_HORIST_H
#define GOMOKU_HORIST_H

#include "gomoku.h"

void init_horist(uint32_t horist[][GAME_SIZE][2]);
uint32_t _calc_horist(BOARD board, uint32_t horist[][GAME_SIZE][2]);

#endif //GOMOKU_HORIST_H
