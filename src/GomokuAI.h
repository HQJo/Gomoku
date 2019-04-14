//
// Created by Kiyoshi on 2019-04-08.
//

#ifndef GOMOKU_GOMOKUAI_H
#define GOMOKU_GOMOKUAI_H

#include <map>
#include <queue>
#include "gomoku.h"
#include "horist.h"
#include "GameBoard.h"


namespace GOMOKUZHQ {
    using pos_t = std::pair<int, int>;
    using update_pos_fun_t = std::function<void(int &, int &)>;

    using evaluate_t = std::pair<float, float>;
    using search_res_t = std::pair<pos_t, float>;
    using candidate_t = std::pair<pos_t, float>;

    using cmp_func_t = std::function<bool(const candidate_t &, const candidate_t &)>;
    using candidate_heap_t = std::priority_queue<candidate_t, std::vector<candidate_t>, cmp_func_t>;

    class GomokuAI {
    public:
        explicit GomokuAI(int _max_depth);

        void init();

        search_res_t search(GameBoard &game_board, int depth, float alpha, float beta);

        float state_evaluate(GameBoard &game_board);

        float pos_evaluate(GameBoard &board, int x, int y);

        float direction_evaluate(GameBoard &game_board, int x, int y, update_pos_fun_t &next, update_pos_fun_t &pre);

        void generate_candidates(GameBoard &game_board);

    private:
        int max_depth;

        std::map<horist_t, float> horist_map;
        candidate_heap_t candidate_heap;
    };
}


#endif //GOMOKU_GOMOKUAI_H
