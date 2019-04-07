#include <iostream>
#include <chrono>
#include <random>
#include "search.h"

using namespace std;
using namespace std::chrono;

int main() {
    BOARD board;
    memset(board, BLANK, sizeof(int) * GAME_SIZE * GAME_SIZE);

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(GAME_SIZE/4-2, 3 * GAME_SIZE/4+2);

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
    print_board(board);
    printf("%f\n", evaluate(board));
    auto start_time = high_resolution_clock::now();

    auto res = alpha_beta_search(board, 1, -numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), true);
    printf("position:(%d, %d)\tscore: %f\n", res.first.first+1, res.first.second+1, res.second);

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(end_time - start_time).count();
    cout << "Search Complete " << duration << " seconds." << endl;
    return 0;
}