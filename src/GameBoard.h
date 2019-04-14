//
// Created by Kiyoshi on 2019-04-14.
//

#ifndef GOMOKU_GAMEBOARD_H
#define GOMOKU_GAMEBOARD_H

#include <vector>
#include "gomoku.h"
#include "horist.h"

namespace GOMOKUZHQ {
    class GameBoard {
        friend class GomokuAI;

    public:
        explicit GameBoard(unsigned board_size);

        void put(int x, int y, int type);

        void unput(int x, int y);

        void print() const;

    private:
        unsigned m_board_size;
        board_t m_board;
        horist_t m_horist_val{0};
        horist_table_t horist_tab;
        bool m_is_black_round{true};
    };

}


#endif //GOMOKU_GAMEBOARD_H
