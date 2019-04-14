//
// Created by Kiyoshi on 2019-04-14.
//

#include "GameBoard.h"

namespace GOMOKUZHQ {
    GameBoard::GameBoard(const unsigned board_size) : m_board_size(board_size) {
        m_board.resize(m_board_size);
        horist_tab[0].resize(m_board_size);
        horist_tab[1].resize(m_board_size);
        for (int i = 0; i < m_board_size; ++i) {
            m_board[i] = std::vector<int>(m_board_size, BLANK);
            horist_tab[0][i].resize(m_board_size, 0);
            horist_tab[1][i].resize(m_board_size, 0);
        }
        init_horist(horist_tab);
    }

    void GameBoard::put(int x, int y, int type) {
        m_board[x][y] = type;
        m_horist_val ^= horist_tab[m_board[x][y] - 1][x][y];
    }

    void GameBoard::unput(const int x, const int y) {
        m_horist_val ^= horist_tab[m_board[x][y] - 1][x][y];
        m_board[x][y] = BLANK;
    }

    void GameBoard::print() const {
        print_board(m_board);
    }

}

