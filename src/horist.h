//
// Created by Kiyoshi on 2019-04-07.
//

#ifndef GOMOKU_HORIST_H
#define GOMOKU_HORIST_H

#include "gomoku.h"

namespace GOMOKUZHQ {
    using horist_t = uint32_t;
    using horist_table_t = std::vector<std::vector<horist_t>>[2];

    void init_horist(horist_table_t table);
}

#endif //GOMOKU_HORIST_H
