//
// Created by Kiyoshi on 2019-04-08.
//

#include <gtest/gtest.h>
#include <chrono>
#include <limits>
#include <random>

using namespace std;
using namespace std::chrono;

TEST(search, c1) {
    BOARD board;
    memset(board, BLANK, sizeof(int) * GAME_SIZE * GAME_SIZE);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(GAME_SIZE/4-2, 3 * GAME_SIZE/4+2);

    float total_time = 0;
    int TIMES = 30;
    for (int t = 0;t < TIMES;++t) {
        memset(board, BLANK, sizeof(int) * GAME_SIZE * GAME_SIZE);
        int i, j;
        for (int k = 0; k < 15; ++k) {
            while (true) {
                i = dis(gen);
                j = dis(gen);
                if (board[i][j] == BLANK) {
                    board[i][j] = BLACK;
                    break;
                }
            }
            while (true) {
                i = dis(gen);
                j = dis(gen);
                if (board[i][j] == BLANK) {
                    board[i][j] = WHITE;
                    break;
                }
            }
        }

        AlphaBetaAI ai(12);
        print_board(board);

        uint32_t horist_val = ai.calc_horist(board);
        auto start_time = high_resolution_clock::now();
        auto res = ai.search(board, 1, -numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), true, horist_val);
        printf("position:(%d, %d)\tscore: %f\n", res.first.first+1, res.first.second+1, res.second);
        auto end_time = high_resolution_clock::now();

        auto duration = duration_cast<seconds>(end_time - start_time).count();
        cout << "Search Complete " << duration << " seconds." << endl;
        total_time += duration;
    }
    printf("Average time: %f\n", total_time / TIMES);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
