//
// Created by Kiyoshi on 2019-04-08.
//

#ifndef GOMOKU_GOMOKUAI_H
#define GOMOKU_GOMOKUAI_H

#include <map>
#include <queue>
#include "gomoku.h"
#include "horist.h"

using pos_t = std::pair<int, int>;
using update_pos_fun_t = std::function<void(int &, int &)>;

using evaluate_t = std::pair<float, float>;
using search_res_t = std::pair<pos_t, float>;
using candidate_t = std::pair<pos_t, float>;

using cmp_func_t = std::function<bool(const candidate_t &, const candidate_t &)>;
using candidate_heap_t = std::priority_queue<candidate_t, std::vector<candidate_t>, cmp_func_t>;

class GomokuAI {
public:
    GomokuAI(int _max_depth, bool is_black=true);

    void init();

    float direction_evaluate(int x, int y, update_pos_fun_t &next, update_pos_fun_t &pre);

    float state_evaluate();

    search_res_t search(int depth, float alpha, float beta);

    void generate_candidates();

    float pos_evaluate(int x, int y);

    void put(int x, int y, bool _is_black);

    void unput(int x, int y);

    int state_at_xy(int x, int y);

    void print_board();
private:
    BOARD board;
    int max_depth;

    bool is_black;
    horist_t horist_val{0};
    horist_t horist_tab[GAME_SIZE][GAME_SIZE][2];
    std::map<horist_t, float> horist_map;
    candidate_heap_t candidate_heap;
};


#endif //GOMOKU_GOMOKUAI_H
