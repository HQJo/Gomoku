//
// Created by Kiyoshi on 2019-04-08.
//

#include <cmath>
#include "GomokuAI.h"

namespace GOMOKUZHQ {
    GomokuAI::GomokuAI(const int _max_depth) : max_depth(_max_depth) {
        init();
    }

    void GomokuAI::init() {
        cmp_func_t candidate_cmp = [](const candidate_t &x, const candidate_t &y) {
            return x.second < y.second;
        };
        candidate_heap = candidate_heap_t(candidate_cmp);
    }

    float GomokuAI::state_evaluate(GameBoard &game_board) {
        int size = game_board.m_board_size;
        bool &is_black = game_board.m_is_black_round;
        horist_t &horist_val = game_board.m_horist_val;
        board_t &board = game_board.m_board;

        float score;
        if (horist_map.find(horist_val) != horist_map.end()) {
            return is_black ? horist_map[horist_val] : -horist_map[horist_val];
        }

        float black_score = 0.0, white_score = 0.0;
        // horizontal search
        update_pos_fun_t next = [](int &x, int &y) { ++y; };
        update_pos_fun_t pre = [](int &x, int &y) { --y; };
        for (int i = 0; i < size; ++i) {
            int j = 0;
            while (j < size) {
                while (j < size && BLANK == board[i][j])
                    next(i, j);
                if (j >= size)
                    break;

                score = direction_evaluate(game_board, i, j, next, pre);
                if (score >= 100000) {
                    horist_map[horist_val] = is_black ? score : -score;
                    if (is_black)
                        return (board[i][j] == BLACK) ? score : -score;
                    else
                        return (board[i][j] == BLACK) ? -score : score;
                }
                if (board[i][j] == BLACK)
                    black_score += score;
                else
                    white_score += score;

                // find next evaluate position
                int j0 = j + 1;
                while (j0 < size) {
                    if (j0 >= j + 5 || board[i][j0] == 3 - board[i][j])
                        break;
                    next(i, j0);
                }
                j = j0;
            }
        }

        // vertical search
        next = [](int &x, int &y) { ++x; };
        pre = [](int &x, int &y) { --x; };
        for (int j = 0; j < size; ++j) {
            int i = 0;
            while (i < size) {
                while (i < size && board[i][j] == BLANK)
                    next(i, j);
                if (i >= size)
                    break;

                score = direction_evaluate(game_board, i, j, next, pre);
                if (score >= 100000) {
                    horist_map[horist_val] = is_black ? score : -score;
                    if (is_black)
                        return (board[i][j] == BLACK) ? score : -score;
                    else
                        return (board[i][j] == BLACK) ? -score : score;
                }
                if (board[i][j] == BLACK)
                    black_score += score;
                else
                    white_score += score;

                int i0 = i + 1;
                while (i0 < size) {
                    if (i0 >= i + 5 || board[i0][j] == 3 - board[i][j])
                        break;
                    next(i0, j);
                }
                i = i0;
            }
        }

        // diagonal search
        int i, j;
        next = [](int &x, int &y) { ++x, ++y; };
        pre = [](int &x, int &y) { --x, --y; };

        i = 0;
        for (j = 0; j < size; ++j) {
            int i0 = i, j0 = j;
            while (i0 < size && j0 < size) {
                while (i0 < size && j0 < size && board[i0][j0] == BLANK)
                    next(i0, j0);
                if (i0 >= size || j0 >= size)
                    break;

                score = direction_evaluate(game_board, i0, j0, next, pre);
                if (score >= 100000) {
                    horist_map[horist_val] = is_black ? score : -score;
                    if (is_black)
                        return (board[i][j] == BLACK) ? score : -score;
                    else
                        return (board[i][j] == BLACK) ? -score : score;
                }
                if (board[i0][j0] == BLACK)
                    black_score += score;
                else
                    white_score += score;

                int ii = i0 + 1, jj = j0 + 1;
                while (ii < size && jj < size) {
                    if (ii >= i0 + 5 || board[ii][jj] == 3 - board[i0][j0])
                        break;
                    next(ii, jj);
                }
                i0 = ii, j0 = jj;
            }
        }

        j = 0;
        for (i = 1; i < size; ++i) {
            int i0 = i, j0 = j;
            while (i0 < size && j0 < size) {
                while (i0 < size && j0 < size && board[i0][j0] == BLANK)
                    next(i0, j0);
                if (i0 >= size || j0 >= size)
                    break;

                score = direction_evaluate(game_board, i0, j0, next, pre);
                if (score >= 100000) {
                    horist_map[horist_val] = is_black ? score : -score;
                    if (is_black)
                        return (board[i][j] == BLACK) ? score : -score;
                    else
                        return (board[i][j] == BLACK) ? -score : score;
                }
                if (board[i0][j0] == BLACK)
                    black_score += score;
                else
                    white_score += score;

                int ii = i0 + 1, jj = j0 + 1;
                while (ii < size && jj < size) {
                    if (ii >= i0 + 5 || board[ii][jj] == 3 - board[i0][j0])
                        break;
                    next(ii, jj);
                }
                i0 = ii, j0 = jj;
            }
        }

        // minor diagonal search
        next = [](int &x, int &y) { ++x, --y; };
        pre = [](int &x, int &y) { --x, ++y; };

        i = 0;
        for (j = 0; j < size; ++j) {
            int i0 = i, j0 = j;
            while (i0 < size && j0 >= 0) {
                while (i0 < size && j0 >= 0 && board[i0][j0] == BLANK)
                    next(i0, j0);
                if (i0 < 0 || i0 >= size || j0 < 0 || j0 >= size)
                    break;

                score = direction_evaluate(game_board, i0, j0, next, pre);
                if (score >= 100000) {
                    horist_map[horist_val] = is_black ? score : -score;
                    if (is_black)
                        return (board[i][j] == BLACK) ? score : -score;
                    else
                        return (board[i][j] == BLACK) ? -score : score;
                }
                if (board[i0][j0] == BLACK)
                    black_score += score;
                else
                    white_score += score;

                int ii = i0 + 1, jj = j0 + 1;
                while (ii < size && jj >= 0) {
                    if (ii >= i0 + 5 || board[ii][jj] == 3 - board[i0][j0])
                        break;
                    next(ii, jj);
                }
                i0 = ii, j0 = jj;
            }
        }

        j = size - 1;
        for (i = 1; i < size; ++i) {
            int i0 = i, j0 = j;
            while (i0 < size && j0 >= 0) {
                while (i0 < size && j0 >= 0 && board[i0][j0] == BLANK)
                    next(i0, j0);
                if (i0 < 0 || i0 >= size || j0 < 0 || j0 >= size)
                    break;

                score = direction_evaluate(game_board, i0, j0, next, pre);
                if (score >= 100000) {
                    horist_map[horist_val] = is_black ? score : -score;
                    if (is_black)
                        return (board[i][j] == BLACK) ? score : -score;
                    else
                        return (board[i][j] == BLACK) ? -score : score;
                }
                if (board[i0][j0] == BLACK)
                    black_score += score;
                else
                    white_score += score;

                int ii = i0 + 1, jj = j0 + 1;
                while (ii < size && jj >= 0) {
                    if (ii >= i0 + 5 || board[ii][jj] == 3 - board[i0][j0])
                        break;
                    next(ii, jj);
                }
                i0 = ii, j0 = jj;
            }
        }

        float ret = is_black ? black_score - white_score : white_score - black_score;
        horist_map[horist_val] = is_black ? ret : -ret;
        return ret;
    }

    search_res_t GomokuAI::search(GameBoard &game_board, int depth, float alpha, float beta) {
        bool is_black = game_board.m_is_black_round;
        board_t &board = game_board.m_board;

        float score;
        if (depth > max_depth) {
            score = state_evaluate(game_board);
            return std::make_pair(std::make_pair(-1, -1), score);
        }
        pos_t opt_move;

        generate_candidates(game_board);
        while (!candidate_heap.empty()) {
            candidate_t p = candidate_heap.top();
            candidate_heap.pop();

            pos_t pos = p.first;
            int x = pos.first, y = pos.second;
            if (board[x][y] == BLANK) {
                game_board.put(x, y, is_black ? BLACK : WHITE);
                is_black = !is_black;

                search_res_t res = search(game_board, depth + 1, -beta, -alpha);
                score = -res.second;

                is_black = !is_black;
                game_board.unput(x, y);
                if (score > alpha) {
                    opt_move = std::make_pair(x, y);
                    if (score >= beta) {
                        return std::make_pair(opt_move, beta);
                    }
                    alpha = score;
                }
            }
        }

        return std::make_pair(opt_move, alpha);
    }

    void GomokuAI::generate_candidates(GameBoard &game_board) {
        int size = game_board.m_board_size;
        board_t &board = game_board.m_board;

        cmp_func_t candidate_cmp = [](const candidate_t &x, const candidate_t &y) {
            return x.second < y.second;
        };
        candidate_heap = candidate_heap_t(candidate_cmp);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == BLANK) {
                    float score = pos_evaluate(game_board, i, j);
                    candidate_heap.push(std::make_pair(std::make_pair(i, j), score));
                }
            }
        }
    }

    float
    GomokuAI::direction_evaluate(GameBoard &game_board, int x, int y, update_pos_fun_t &next, update_pos_fun_t &pre) {
        int size = game_board.m_board_size;
        board_t &board = game_board.m_board;

        int i0 = x, j0 = y;
        pre(i0, j0);
        bool left_blocked = false;
        if (i0 < 0 || i0 > size || j0 < 0 || j0 > size || (board[i0][j0] == 3 - board[x][y]))
            left_blocked = true;
        bool right_blocked = false, out_of_board = false;

        i0 = x, j0 = y;
        int self = 0, blank = 0, pos;
        for (pos = 1; pos < 6; ++pos, next(i0, j0)) {
            if (i0 < 0 || j0 < 0 || i0 >= size || j0 >= size) {
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

        auto pos_score = static_cast<float>(-(std::pow(x - size / 2, 2) + std::pow(y - size / 2, 2)) / 100);
        switch (self) {
            case 1:
                return 0 + pos_score;
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

    float GomokuAI::pos_evaluate(GameBoard &board, int x, int y) {
        bool is_black = board.m_is_black_round;
        board.put(x, y, is_black ? BLACK : WHITE);
        float score_after = state_evaluate(board);
        board.unput(x, y);
        float score_before = state_evaluate(board);
        return score_after - score_before;
    }

}
