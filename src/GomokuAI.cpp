//
// Created by Kiyoshi on 2019-04-08.
//

#include "GomokuAI.h"
#include "horist.h"

GomokuAI::GomokuAI(const int _max_depth, const bool _is_black) : max_depth(_max_depth), is_black(_is_black) {
    init();
}

void GomokuAI::init() {
    memset(board, BLANK, sizeof(board));
    cmp_func_t candidate_cmp = [](const candidate_t &x, const candidate_t &y) {
        return x.second < y.second;
    };
    candidate_heap = candidate_heap_t(candidate_cmp);
    init_horist(horist_tab);
}

float GomokuAI::state_evaluate() {
    float score;
    if (horist_map.find(horist_val) != horist_map.end()) {
        return is_black ? -horist_map[horist_val] : horist_map[horist_val];
    }

    float black_score = 0.0, white_score = 0.0;
    // horizontal search
    update_pos_fun_t next = [](int &x, int &y) { ++y; };
    update_pos_fun_t pre = [](int &x, int &y) { --y; };
    for (int i = 0; i < GAME_SIZE; ++i) {
        int j = 0;
        while (j < GAME_SIZE) {
            while (board[i][j] == BLANK && j < GAME_SIZE)
                next(i, j);
            if (j >= GAME_SIZE)
                break;

            score = direction_evaluate(i, j, next, pre);
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

            score = direction_evaluate(i, j, next, pre);
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

            score = direction_evaluate(i0, j0, next, pre);
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

            score = direction_evaluate(i0, j0, next, pre);
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

            score = direction_evaluate(i0, j0, next, pre);
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

            score = direction_evaluate(i0, j0, next, pre);
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
    horist_map[horist_val] = is_black ? -ret : ret;
    return ret;
}

search_res_t GomokuAI::search(int depth, float alpha, float beta) {
    float score;
    if (depth > max_depth) {
        score = state_evaluate();
        return std::make_pair(std::make_pair(-1, -1), score);
    }
    pos_t opt_move;

    generate_candidates();
    while (!candidate_heap.empty()) {
        candidate_t p = candidate_heap.top();
        candidate_heap.pop();

        pos_t pos = p.first;
        int x = pos.first, y = pos.second;
        if (board[x][y] == BLANK) {
            put(x, y, is_black);

            is_black = !is_black;
            search_res_t res = search(depth + 1, -beta, -alpha);
            is_black = !is_black;
            score = -res.second;
            if (score > alpha) {
                opt_move = std::make_pair(x, y);
                if (score >= beta) {
                    board[x][y] = BLANK;
                    return std::make_pair(opt_move, beta);
                }
                alpha = score;
            }
            unput(x, y);
        }
    }

    return std::make_pair(opt_move, alpha);
}

void GomokuAI::generate_candidates() {
    cmp_func_t candidate_cmp = [](const candidate_t &x, const candidate_t &y) {
        return x.second < y.second;
    };
    candidate_heap = candidate_heap_t(candidate_cmp);
    for (int i = 0; i < GAME_SIZE; ++i) {
        for (int j = 0; j < GAME_SIZE; ++j) {
            if (board[i][j] == BLANK) {
                float score = pos_evaluate(i, j);
                candidate_heap.push(std::make_pair(std::make_pair(i, j), score));
            }
        }
    }
}

float GomokuAI::direction_evaluate(int x, int y, update_pos_fun_t &next, update_pos_fun_t &pre) {
    int i0 = x, j0 = y;
    pre(i0, j0);
    bool left_blocked = false;
    if (i0 < 0 || i0 > GAME_SIZE || j0 < 0 || j0 > GAME_SIZE || (board[i0][j0] == 3 - board[x][y]))
        left_blocked = true;
    bool right_blocked = false, out_of_board = false;

    i0 = x, j0 = y;
    int self = 0, blank = 0, pos;
    for (pos = 1; pos < 6; ++pos, next(i0, j0)) {
        if (i0 < 0 || j0 < 0 || i0 >= GAME_SIZE || j0 >= GAME_SIZE) {
            out_of_board = true;
            break;
        }
        if (board[i0][j0] == BLANK) {
            blank = blank * 10 + pos;
        } else if (board[i0][j0] == board[x][y]) {
            self++;
        } else if (board[i0][j0] == 3 - board[x][y]) {
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
    };
}

float GomokuAI::pos_evaluate(int x, int y) {
    put(x, y, is_black);
    float score_after = state_evaluate();
    unput(x, y);
    float score_before = state_evaluate();
    return score_after - score_before;
}

void GomokuAI::put(int x, int y, bool _is_black) {
    board[x][y] = _is_black ? BLACK : WHITE;
    horist_val ^= horist_tab[x][y][board[x][y]-1];
}

void GomokuAI::unput(int x, int y) {
    horist_val ^= horist_tab[x][y][board[x][y]-1];
    board[x][y] = BLANK;
}

int GomokuAI::state_at_xy(int x, int y) {
    return board[x][y];
}

void GomokuAI::print_board() {
    ::print_board(board);
}
