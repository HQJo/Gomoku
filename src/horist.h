//
// Created by Kiyoshi on 2019-04-07.
//

#ifndef GOMOKU_HORIST_H
#define GOMOKU_HORIST_H

#include "gomoku.h"

using horist_t = uint32_t;
void init_horist(horist_t horist[][GAME_SIZE][2]);
horist_t _calc_horist(BOARD board, horist_t horist[][GAME_SIZE][2]);

#endif //GOMOKU_HORIST_H
