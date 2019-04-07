//
// Created by Kiyoshi on 2019-04-07.
//

#ifndef GOMOKU_ALPHABETAAI_H
#define GOMOKU_ALPHABETAAI_H

#include <utility>
#include <limits>
#include <functional>
#include <bitset>
#include <vector>
#include <queue>
#include <map>
#include "gomoku.h"

using pos_type = std::pair<int, int>;
using search_res = std::pair<pos_type, float>;
using heuristic_score = std::pair<pos_type, float>;
using cmp_func = std::function<bool(heuristic_score, heuristic_score)>;
const cmp_func heuristic_cmp = [](heuristic_score x, heuristic_score y) {
    return x.second < y.second;
};
using update_pos_func = std::function<void(int &, int &)>;

class AlphaBetaAI {
public:
    explicit AlphaBetaAI(int _max_depth = 4);

    void init();

    search_res search(BOARD board, int depth, float alpha, float beta, bool is_black, uint32_t horist_val);

    float direction_evaluate(BOARD board, int i, int j, const update_pos_func &next, const update_pos_func &pre);

    float evaluate(BOARD board, bool is_black, uint32_t horist_val);

    void heuristic_gen(BOARD board, bool is_black, uint32_t horist_val);

    float heuristic_evaluate(BOARD board, int x, int y, bool is_black, uint32_t horist_val);

    uint32_t calc_horist(BOARD board);

private:
    int max_depth;
    std::map<uint32_t, float> horist_map;
    std::priority_queue<heuristic_score, std::vector<heuristic_score>, cmp_func> heuristic_heap{heuristic_cmp};
    uint32_t horist[GAME_SIZE][GAME_SIZE][2];
};


#endif //GOMOKU_ALPHABETAAI_H
