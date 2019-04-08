#include <iostream>
#include <chrono>
#include <random>
#include <limits>
#include "GomokuAI.h"

using namespace std::chrono;

int main() {
    GomokuAI ai(8);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(GAME_SIZE/4-2, 3 * GAME_SIZE/4+2);

    int i, j;
    for (int k = 0; k < 15; ++k) {
        while (true) {
            i = dis(gen);
            j = dis(gen);
            if (ai.state_at_xy(i, j) == BLANK) {
                ai.put(i, j, true);
                break;
            }
        }
        while (true) {
            i = dis(gen);
            j = dis(gen);
            if (ai.state_at_xy(i, j) == BLANK) {
                ai.put(i, j, false);
                break;
            }
        }
    }

    ai.print_board();

    auto start_time = high_resolution_clock::now();
    auto res = ai.search(1, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
    auto end_time = high_resolution_clock::now();
    printf("Pos:(%d, %d)\tScore:%f\n", res.first.first+1, res.first.second+1, res.second);

    auto duration = duration_cast<seconds>(end_time - start_time).count();
    std::cout << "Search Complete " << duration << " seconds." << std::endl;

    return 0;
}