//
// Created by Kiyoshi on 2019-04-01.
//

#ifndef GOMOKU_GOMOKU_H
#define GOMOKU_GOMOKU_H
#include <cstdio>
#include <functional>

const int GAME_SIZE = 15;
const int BLANK = 0, BLACK = 1, WHITE = 2;
using BOARD = int[GAME_SIZE][GAME_SIZE];

void print_board(BOARD board);

#endif //GOMOKU_GOMOKU_H
