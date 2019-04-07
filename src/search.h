//
// Created by Kiyoshi on 2019-04-01.
//

#ifndef GOMOKU_SEARCH_H
#define GOMOKU_SEARCH_H

#include <utility>
#include <limits>
#include <functional>
#include "gomoku.h"

const int MAX_DEPTH = 4;

using pos_type = std::pair<int, int>;
using search_res = std::pair<pos_type, float>;
using update_pos_func = std::function<void(int &, int &)>;

float
direction_evaluate(BOARD board, const int i, const int j, const update_pos_func &next, const update_pos_func &pre) {
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


float evaluate(BOARD board, const bool is_black = true) {
    float black_score = 0.0, white_score = 0.0;
    float score;

    // horizontal search
    update_pos_func next = [](int &x, int &y) { ++y; };
    update_pos_func pre = [](int &x, int &y) { --y; };
    for (int i = 0; i < GAME_SIZE; ++i) {
        int j = 0;
        while (j < GAME_SIZE) {
            while (board[i][j] == BLANK && j < GAME_SIZE)
                next(i, j);
            if (j >= GAME_SIZE)
                break;

            score = direction_evaluate(board, i, j, next, pre);
            if (board[i][j] == BLACK)
                black_score += score;
            else
                white_score += score;

            int j0 = j + 1;
            if (j0 < GAME_SIZE) {
                while (board[i][j0] == board[i][j])
                    next(i, j0);
            }
            while (j0 < GAME_SIZE && board[i][j0] != 3 - board[i][j])
                next(i, j0);
            j = j0;
        }
    }

    // vertical search
    next = [](int &x, int &y) { ++x; };
    pre = [](int &x, int &y) { --x; };
    for (int j = 0; j < GAME_SIZE; ++j) {
        int i = 0;
        while (i < GAME_SIZE) {
            while (board[i][j] == BLANK && i < GAME_SIZE)
                next(i, j);
            if (i >= GAME_SIZE)
                break;

            score = direction_evaluate(board, i, j, next, pre);
            if (board[i][j] == BLACK)
                black_score += score;
            else
                white_score += score;

            int i0 = i + 1;
            while (i0 < GAME_SIZE && board[i0][j] == board[i][j])
                next(i0, j);
            while (i0 < GAME_SIZE && board[i0][j] != 3 - board[i][j])
                next(i0, j);
            i = i0;
        }
    }

    // diagonal search
    int i, j;
    next = [](int &x, int &y) { ++x, ++y; };
    pre = [](int &x, int &y) { --x, --y; };

    i = 0;
    for (j = 0; j < GAME_SIZE; ++j) {
        int i0 = i, j0 = j;
        while (i0 < GAME_SIZE && j0 < GAME_SIZE) {
            while (board[i0][j0] == BLANK && i0 < GAME_SIZE && j0 < GAME_SIZE)
                next(i0, j0);
            if (i0 >= GAME_SIZE || j0 >= GAME_SIZE)
                break;

            score = direction_evaluate(board, i0, j0, next, pre);
            if (board[i0][j0] == BLACK)
                black_score += score;
            else
                white_score += score;

            int ii = i0, jj = j0;
            while (ii < GAME_SIZE && jj < GAME_SIZE && board[ii][jj] == board[i0][j0])
                next(ii, jj);
            while (ii < GAME_SIZE && jj < GAME_SIZE && board[ii][jj] != 3 - board[i0][j0])
                next(ii, jj);
            i0 = ii, j0 = jj;
        }
    }

    j = 0;
    for (i = 1; i < GAME_SIZE; ++i) {
        int i0 = i, j0 = j;
        while (i0 < GAME_SIZE && j0 < GAME_SIZE) {
            while (board[i0][j0] == BLANK && i0 < GAME_SIZE && j0 < GAME_SIZE)
                next(i0, j0);
            if (i0 >= GAME_SIZE || j0 >= GAME_SIZE)
                break;

            score = direction_evaluate(board, i0, j0, next, pre);
            if (board[i0][j0] == BLACK)
                black_score += score;
            else
                white_score += score;

            int ii = i0, jj = j0;
            while (ii < GAME_SIZE && jj < GAME_SIZE && board[ii][jj] == board[i0][j0])
                next(ii, jj);
            while (ii < GAME_SIZE && jj < GAME_SIZE && board[ii][jj] != 3 - board[i0][j0])
                next(ii, jj);
            i0 = ii, j0 = jj;
        }
    }

    // minor diagonal search
    next = [](int &x, int &y) { ++x, --y; };
    pre = [](int &x, int &y) { --x, ++y; };

    i = 0;
    for (j = 0; j < GAME_SIZE; ++j) {
        int i0 = i, j0 = j;
        while (i0 < GAME_SIZE && j0 < GAME_SIZE) {
            while (board[i0][j0] == BLANK)
                next(i0, j0);
            if (i0 < 0 || i0 >= GAME_SIZE || j0 < 0 || j0 >= GAME_SIZE)
                break;

            score = direction_evaluate(board, i0, j0, next, pre);
            if (board[i0][j0] == BLACK)
                black_score += score;
            else
                white_score += score;

            int ii = i0, jj = j0;
            while (ii < GAME_SIZE && jj >= 0 && board[ii][jj] == board[i0][j0])
                next(ii, jj);
            while (ii < GAME_SIZE && jj >= 0 && board[ii][jj] != 3 - board[i0][j0])
                next(ii, jj);
            i0 = ii, j0 = jj;
        }
    }

    j = GAME_SIZE - 1;
    for (i = 1; i < GAME_SIZE; ++i) {
        int i0 = i, j0 = j;
        while (i0 < GAME_SIZE && j0 < GAME_SIZE) {
            while (board[i0][j0] == BLANK)
                next(i0, j0);
            if (i0 < 0 || i0 >= GAME_SIZE || j0 < 0 || j0 >= GAME_SIZE)
                break;

            score = direction_evaluate(board, i0, j0, next, pre);
            if (board[i0][j0] == BLACK)
                black_score += score;
            else
                white_score += score;

            int ii = i0, jj = j0;
            while (ii < GAME_SIZE && jj >= 0 && board[ii][jj] == board[i0][j0])
                next(ii, jj);
            while (ii < GAME_SIZE && jj >= 0 && board[ii][jj] != 3 - board[i0][j0])
                next(ii, jj);
            i0 = ii, j0 = jj;
        }
    }

    return is_black ? black_score - white_score : white_score - black_score;
}

search_res alpha_beta_search(BOARD board, const int depth, float alpha, float beta, const bool is_black) {
    float score = 0.0;
    if (depth > MAX_DEPTH) {
        score = evaluate(board, is_black);
        return std::make_pair(std::make_pair(-1, -1), score);
    }
    pos_type opt_move;

    std::function<void(int &, int &)> directions[4]{
            [](int &x, int &y) { ++x; },
            [](int &x, int &y) { ++y; },
            [](int &x, int &y) { --x; },
            [](int &x, int &y) { --y; }
    };
    int d = 0;

    int x = (GAME_SIZE - 1) / 2, y = (GAME_SIZE - 1) / 2;
    while (x >= 0 && x < GAME_SIZE && y >= 0 && y < GAME_SIZE) {
        int steps = (d / 2) + 1;
        for (int i = 0; i < steps; ++i) {
            if (board[x][y] == BLANK) {
                board[x][y] = is_black? BLACK : WHITE;
                search_res res = alpha_beta_search(board, depth + 1, -beta, -alpha, !is_black);
                score = -res.second;
                if (score > alpha) {
                    opt_move = std::make_pair(x, y);
                    if (score >= beta) {
                        board[x][y] = BLANK;
                        return std::make_pair(opt_move, beta);
                    }
                    alpha = score;
//                    printf("Pos:(%d, %d), score: %f\n", x+1, y+1, score);
                }
                board[x][y] = BLANK;
            }
            directions[d % 4](x, y);
        }
        ++d;
    }
    return std::make_pair(opt_move, alpha);
}

#endif //GOMOKU_SEARCH_H
