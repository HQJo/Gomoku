//
// Created by Kiyoshi on 2019-04-08.
//

#include <gtest/gtest.h>
#include "../src/GameBoard.h"
#include "../src/GomokuAI.h"
#include <random>

using namespace std;
using namespace std::chrono;
using namespace GOMOKUZHQ;

TEST(search, c1) {
    const int size = 15;
    int board[size][size];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(size / 4 - 2, 3 * size / 4 + 2);

    float total_time = 0;
    const int TIMES = 50;
    for (int t = 0;t < TIMES;++t) {
        GameBoard game_board(size);
        memset(board, 0, size * size * sizeof(int));
        int i, j;
        for (int k = 0; k < 8; ++k) {
            while (true) {
                i = dis(gen);
                j = dis(gen);
                if (board[i][j] == BLANK) {
                    board[i][j] = BLACK;
                    game_board.put(i, j, BLACK);
                    break;
                }
            }
            while (true) {
                i = dis(gen);
                j = dis(gen);
                if (board[i][j] == BLANK) {
                    board[i][j] = WHITE;
                    game_board.put(i, j, WHITE);
                    break;
                }
            }
        }

        GomokuAI ai(12);
        game_board.print();
        printf("Score: %f\n", ai.state_evaluate(game_board));

        auto start_time = high_resolution_clock::now();
        auto res = ai.search(game_board, 1, -numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
        printf("position:(%d, %d)\tscore: %f\n", res.first.first+1, res.first.second+1, res.second);
        auto end_time = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(end_time - start_time).count();
        cout << "Search Complete " << duration << " millseconds." << endl;
        total_time += duration;
    }
    printf("Average time: %f millseconds\n", total_time / TIMES);
}

TEST(defend, case1) {
    GameBoard board{15};
    board.put(7, 7, WHITE);
    board.put(7, 8, WHITE);
    board.put(8, 8, WHITE);
    board.put(8, 9, WHITE);
    board.put(9, 8, WHITE);
    board.put(8, 7, BLACK);
    board.put(9, 7, BLACK);
    board.put(9, 9, BLACK);
    board.put(9, 10, BLACK);
    board.print();
    GomokuAI ai{12};
    auto res = ai.search(board, 1, -numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
    printf("Search res: (%d, %d)\n", res.first.first + 1, res.first.second + 1);
}

TEST(defend, case2) {
    GameBoard board{15};
    board.put(7, 7, WHITE);
    board.put(7, 8, WHITE);
    board.put(8, 8, WHITE);
    board.put(9, 8, WHITE);
    board.put(9, 9, WHITE);

    board.put(8, 7, BLACK);
    board.put(8, 9, BLACK);
    board.put(7, 9, BLACK);
    board.put(10, 8, BLACK);
    board.print();

    GomokuAI ai{12};
    auto res = ai.search(board, 1, -numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
    printf("Search res: (%d, %d)\n", res.first.first + 1, res.first.second + 1);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
