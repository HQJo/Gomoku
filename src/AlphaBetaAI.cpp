//
// Created by Kiyoshi on 2019-04-07.
//

#include "AlphaBetaAI.h"
#include "horist.h"

AlphaBetaAI::AlphaBetaAI(const int _max_depth) : max_depth(_max_depth) {
    init();
}

void AlphaBetaAI::init() {
    init_horist(horist);
}

search_res
AlphaBetaAI::search(BOARD board, const int depth, float alpha, float beta, const bool is_black, uint32_t horist_val) {
    float score;
    if (depth > max_depth) {
        score = evaluate(board, is_black, horist_val);
        return std::make_pair(std::make_pair(-1, -1), score);
    }
    pos_type opt_move;

    update_pos_func directions[4]{
            [](int &x, int &y) { ++x; },
            [](int &x, int &y) { ++y; },
            [](int &x, int &y) { --x; },
            [](int &x, int &y) { --y; }
    };
    int d = 0;

    heuristic_gen(board, is_black, horist_val);
    while (!heuristic_heap.empty()) {
        heuristic_score p = heuristic_heap.top();
        heuristic_heap.pop();

        pos_type pos = p.first;
        int x = pos.first, y = pos.second;
        if (board[x][y] == BLANK) {
            board[x][y] = is_black ? BLACK : WHITE;
            horist_val ^= horist[x][y][board[x][y] - 1];

            search_res res = search(board, depth + 1, -beta, -alpha, !is_black, horist_val);
            score = -res.second;
            if (score > alpha) {
                opt_move = std::make_pair(x, y);
                if (score >= beta) {
                    board[x][y] = BLANK;
                    return std::make_pair(opt_move, beta);
                }
                alpha = score;
            }
            board[x][y] = BLANK;
            horist_val ^= horist[x][y][board[x][y] - 1];
        }
    }

/*    int x = (game_size - 1) / 2, y = (game_size - 1) / 2;
    while (x >= 0 && x < game_size && y >= 0 && y < game_size) {
        int steps = (d / 2) + 1;
        for (int i = 0; i < steps; ++i) {
            if (board[x][y] == blank) {
                board[x][y] = is_black ? black : white;
                horist_val ^= horist[x][y][board[x][y] - 1];

                search_res res = search(board, depth + 1, -beta, -alpha, !is_black, horist_val);
                score = -res.second;
                if (score > alpha) {
                    opt_move = std::make_pair(x, y);
                    if (score >= beta) {
                        board[x][y] = blank;
                        return std::make_pair(opt_move, beta);
                    }
                    alpha = score;
                }
                board[x][y] = blank;
                horist_val ^= horist[x][y][board[x][y] - 1];
            }
            directions[d % 4](x, y);
        }
        ++d;
    }*/
    return std::make_pair(opt_move, alpha);
}

float AlphaBetaAI::direction_evaluate(BOARD board, const int i, const int j, const update_pos_func &next,
                                      const update_pos_func &pre) {
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

float AlphaBetaAI::evaluate(BOARD board, const bool is_black, uint32_t horist_val) {
    float black_score = 0.0, white_score = 0.0;
    float score;
    if (horist_map.find(horist_val) != horist_map.end()) {
        return horist_map[horist_val];
    }

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

    float ret = is_black ? black_score - white_score : white_score - black_score;
    horist_map[horist_val] = ret;
    return ret;
}

uint32_t AlphaBetaAI::calc_horist(BOARD board) {
    return _calc_horist(board, horist);
}

void AlphaBetaAI::heuristic_gen(BOARD board, bool is_black, uint32_t horist_val) {
    heuristic_heap = std::priority_queue<heuristic_score , std::vector<heuristic_score >, cmp_func>(heuristic_cmp);
    for (int i = 0; i < GAME_SIZE; ++i) {
        for (int j = 0; j < GAME_SIZE; ++j) {
            if (board[i][j] == BLANK) {
                float score = heuristic_evaluate(board, i, j, is_black, 0);
                heuristic_heap.push(std::make_pair(std::make_pair(i, j), score));
            }
        }
    }
}

float AlphaBetaAI::heuristic_evaluate(BOARD board, const int x, const int y, bool is_black, uint32_t horist_val) {
    board[x][y] = is_black ? BLACK : WHITE;
    float score_after = this->evaluate(board, is_black, horist_val ^ horist[x][y][is_black?0 : 1]);
    board[x][y] = BLANK;
    float score_before = this->evaluate(board, is_black, horist_val);
    return score_after-score_before;
}
