#include <iostream>

#include "utility.hpp"

namespace {
const std::string XMAS("XMAS");
const std::string MAS("MAS");
const std::string SAM("SAM");
} // namespace

bool searchXMAS(const std::vector<std::string>& grid, int r, int c, const int m, const int n,
                const int dirX, const int dirY, int i)
{
    // Bounds checking
    if (r < 0 || r >= m || c < 0 || c >= n) {
        return false;
    }

    if (grid[r][c] != XMAS[i]) {
        return false;
    }

    if (i == XMAS.size() - 1) {
        return true;
    }

    return searchXMAS(grid, r + dirY, c + dirX, m, n, dirX, dirY, i + 1);
}

void solveDay4()
{
    using namespace std;

    auto grid = getInputLines("../input/day4.input");
    const auto m = grid.size();
    const auto n = grid.front().size();

    // *** Part 1 ***
    auto count = 0;

    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] != XMAS.front()) {
                continue;
            }

            // Start the search in all directions
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0) { // it doesn't mean a direction
                        continue;
                    }
                    if (searchXMAS(grid, r, c, m, n, i, j, 0)) {
                        ++count;
                    }
                }
            }
        }
    }

    cout << "Part 1: " << count << endl;

    // *** Part 2 ***
    count = 0; // Reset the counter before part 2

    for (int r = 0; r < m - 2; ++r) {
        for (int c = 0; c < n - 2; ++c) {
            if (grid[r][c] == MAS.front() || grid[r][c] == SAM.front()) {
                string current;
                current.push_back(grid[r][c]);
                current.push_back(grid[r + 1][c + 1]);
                current.push_back(grid[r + 2][c + 2]);

                if (current != SAM && current != MAS) {
                    continue;
                }

                current = "";
                auto rr = r;
                auto cc = c + 2;

                current.push_back(grid[rr][cc]);
                current.push_back(grid[rr + 1][cc - 1]);
                current.push_back(grid[rr + 2][cc - 2]);

                if (current == SAM || current == MAS) {
                    ++count;
                }
            }
        }
    }

    cout << "Part 2: " << count << endl;
}
