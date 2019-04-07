//
// Created by Kiyoshi on 2019-04-02.
//

#include "../src/gomoku.h"
#include "../src/AlphaBetaAI.h"
#include <gtest/gtest.h>

AlphaBetaAI ai(4);

TEST(live4, case1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][3] = board[1][4] = board[1][5] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 10000);
}

TEST(death4, case1_1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][3] = board[1][4] = board[1][5] = BLACK;
    board[1][6] = WHITE;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(death4, border1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][0] = board[1][1] = board[1][2] = board[1][3] = BLACK;
    board[1][4] = WHITE;
    EXPECT_EQ(ai.evaluate(board), 0);
}

TEST(death4, case1_2) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = WHITE;
    board[1][3] = board[1][4] = board[1][5] = board[1][6] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(death4, case2_1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][3] = board[1][4] = board[1][6] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(death4, case2_2) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][4] = board[1][5] = board[1][6] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(death4, case3) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][3] = board[1][5] = board[1][6] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(live3, case1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][3] = board[1][4] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(live3, border1_1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][1] = board[1][2] = board[1][3] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(live3, border1_2) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    for (int i = 1;i < 4;++i)
        board[1][GAME_SIZE-i-1] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(live3, case2_1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][3] = board[1][5] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(live3, case2_2) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][4] = board[1][5] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(live3, border2_1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][0] = board[1][1] = board[1][3] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 100);
}

TEST(live3, border2_2) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][1] = board[1][2] = board[1][4] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(live3, border2_3) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][GAME_SIZE-1] = board[1][GAME_SIZE-2] = board[1][GAME_SIZE-4] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 100);
}

TEST(live3, border2_4) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][GAME_SIZE-2] = board[1][GAME_SIZE-3] = board[1][GAME_SIZE-5] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 1000);
}

TEST(death3, case1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][1] = board[1][3] = board[1][5] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 100);
}

TEST(death3, case2_1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][1] = board[1][2] = board[1][5] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 100);
}

TEST(death3, case2_2) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][1] = board[1][4] = board[1][5] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 100);
}

TEST(death3, case3_1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][1] = WHITE;
    board[1][2] = board[1][3] = board[1][4] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 100);
}

TEST(death3, case3_2) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][3] = board[1][4] = board[1][5] = BLACK;
    board[1][6] = WHITE;
    EXPECT_EQ(ai.evaluate(board), 100);
}

TEST(death3, case4_1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][1] = WHITE;
    board[1][2] = board[1][3] = board[1][5] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 100);
}

TEST(death3, case4_2) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][4] = board[1][5] = BLACK;
    board[1][6] = WHITE;
    EXPECT_EQ(ai.evaluate(board), 100);
}

TEST(live2, case1) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][3] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 100);
}

TEST(live2, case2) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][4] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 100);
}

TEST(live2, case3) {
    BOARD board;
    memset(board, BLANK, sizeof(board));
    board[1][2] = board[1][4] = BLACK;
    EXPECT_EQ(ai.evaluate(board), 100);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}