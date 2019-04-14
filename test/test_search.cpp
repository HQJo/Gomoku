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
    GameBoard game_board(size);
    int board[size][size];
    memset(board, 0, sizeof(board));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(size / 4 - 2, 3 * size / 4 + 2);

    float total_time = 0;
    int TIMES = 1;
    for (int t = 0;t < TIMES;++t) {
        int i, j;
        for (int k = 0; k < 15; ++k) {
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
        game_board.print();

        GomokuAI ai(12);
        auto start_time = high_resolution_clock::now();
        auto res = ai.search(game_board, 1, -numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
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
