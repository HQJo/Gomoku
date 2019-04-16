//
// Created by Kiyoshi on 2019-04-07.
//
#include "gomoku.h"
#include "horist.h"
#include <random>

namespace GOMOKUZHQ {
    void init_horist(horist_table_t table) {
        std::random_device r;
        std::seed_seq seed{r()};
        std::independent_bits_engine<std::mt19937, 32, horist_t> engine(seed);

        auto size = table[0].size();
        for (unsigned k = 0; k < 2; ++k) {
            for (unsigned i = 0; i < size; ++i) {
                for (unsigned j = 0; j < size; ++j) {
                    table[k][i][j] = engine();
                }
            }
        }
    }
}
