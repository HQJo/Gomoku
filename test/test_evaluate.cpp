//
// Created by Kiyoshi on 2019-04-02.
//

#include "../src/GameBoard.h"
#include "../src/GomokuAI.h"
#include <gtest/gtest.h>

using namespace GOMOKUZHQ;
const int size = 15;
GomokuAI ai(10);

TEST(live4, case1) {
    GameBoard board(size);
    board.put(1, 2, BLACK);
    board.put(1, 3, BLACK);
    board.put(1, 4, BLACK);
    board.put(1, 5, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 10000);
}

TEST(death4, case1_1) {
    GameBoard board(size);
    for (int i = 2; i < 6; ++i)
        board.put(1, i, BLACK);
    board.put(1, 6, WHITE);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(death4, border1) {
    GameBoard board(size);
    for (int i = 0; i < 4; ++i)
        board.put(1, i, BLACK);
    board.put(1, 4, WHITE);
    EXPECT_EQ(ai.state_evaluate(board), 0);
}

TEST(death4, case1_2) {
    GameBoard board(size);
    for (int i = 3; i < 7; ++i)
        board.put(1, i, BLACK);
    board.put(1, 2, WHITE);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(death4, case2_1) {
    GameBoard board(size);
    for (int i = 2; i < 5; ++i)
        board.put(1, i, BLACK);
    board.put(1, 6, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(death4, case2_2) {
    GameBoard board(size);
    for (int i = 4; i < 7; ++i)
        board.put(1, i, BLACK);
    board.put(1, 2, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(death4, case3) {
    GameBoard board(size);
    board.put(1, 2, BLACK);
    board.put(1, 3, BLACK);
    board.put(1, 5, BLACK);
    board.put(1, 6, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(live3, case1) {
    GameBoard board(size);
    for (int i = 2; i < 5; ++i)
        board.put(1, i, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(live3, border1_1) {
    GameBoard board(size);
    for (int i = 1; i < 4; ++i)
        board.put(1, i, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(live3, border1_2) {
    GameBoard board(size);
    for (int i = 1;i < 4;++i)
        board.put(1, size - i - 1, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(live3, case2_1) {
    GameBoard board(size);
    board.put(1, 2, BLACK);
    board.put(1, 3, BLACK);
    board.put(1, 5, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(live3, case2_2) {
    GameBoard board(size);
    board.put(1, 2, BLACK);
    board.put(1, 4, BLACK);
    board.put(1, 5, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(live3, border2_1) {
    GameBoard board(size);
    board.put(1, 0, BLACK);
    board.put(1, 1, BLACK);
    board.put(1, 3, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 100);
}

TEST(live3, border2_2) {
    GameBoard board(size);
    board.put(1, 1, BLACK);
    board.put(1, 2, BLACK);
    board.put(1, 4, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(live3, border2_3) {
    GameBoard board(size);
    board.put(1, size - 1, BLACK);
    board.put(1, size - 2, BLACK);
    board.put(1, size - 4, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 100);
}

TEST(live3, border2_4) {
    GameBoard board(size);
    board.put(1, size - 2, BLACK);
    board.put(1, size - 3, BLACK);
    board.put(1, size - 5, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 1000);
}

TEST(death3, case1) {
    GameBoard board(size);
    board.put(1, 1, BLACK);
    board.put(1, 3, BLACK);
    board.put(1, 5, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 100);
}

TEST(death3, case2_1) {
    GameBoard board(size);
    board.put(1, 1, BLACK);
    board.put(1, 2, BLACK);
    board.put(1, 5, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 100);
}

TEST(death3, case2_2) {
    GameBoard board(size);
    board.put(1, 1, BLACK);
    board.put(1, 4, BLACK);
    board.put(1, 5, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 100);
}

TEST(death3, case3_1) {
    GameBoard board(size);
    for (int i = 2; i < 5; ++i)
        board.put(1, i, BLACK);
    board.put(1, 1, WHITE);
    EXPECT_EQ(ai.state_evaluate(board), 100);
}

TEST(death3, case3_2) {
    GameBoard board(size);
    for (int i = 3; i < 6; ++i)
        board.put(1, i, BLACK);
    board.put(1, 6, WHITE);
    EXPECT_EQ(ai.state_evaluate(board), 100);
}

TEST(death3, case4_1) {
    GameBoard board(size);
    board.put(1, 2, BLACK);
    board.put(1, 3, BLACK);
    board.put(1, 5, BLACK);
    board.put(1, 1, WHITE);
    EXPECT_EQ(ai.state_evaluate(board), 100);
}

TEST(death3, case4_2) {
    GameBoard board(size);
    board.put(1, 2, BLACK);
    board.put(1, 4, BLACK);
    board.put(1, 5, BLACK);
    board.put(1, 6, WHITE);
    EXPECT_EQ(ai.state_evaluate(board), 100);
}

TEST(live2, case1) {
    GameBoard board(size);
    board.put(1, 2, BLACK);
    board.put(1, 3, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 100);
}

TEST(live2, case2) {
    GameBoard board(size);
    board.put(1, 2, BLACK);
    board.put(1, 3, BLACK);
    EXPECT_EQ(ai.state_evaluate(board), 100);
}

TEST(oppo, case1) {
    GameBoard board(size);
    for (int i = 7; i < 12; ++i)
        board.put(5, i, WHITE);
    EXPECT_EQ(ai.state_evaluate(board), -100000);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}