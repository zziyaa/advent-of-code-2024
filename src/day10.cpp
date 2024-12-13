#include <iostream>
#include <set>

#include "utility.hpp"

using Grid = std::vector<std::vector<int>>;

void search(const Grid& grid, const int r, const int c, const int m, const int n, const int target,
            int& score, int& rating, std::set<std::pair<int, int>>& visited)
{
    if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] != target) {
        return;
    }

    if (target == 9) {
        ++rating;
        if (visited.count(std::make_pair(r, c)) == 0) {
            ++score;
            visited.insert(std::make_pair(r, c));
        }
        return;
    }

    search(grid, r + 1, c, m, n, target + 1, score, rating, visited);
    search(grid, r - 1, c, m, n, target + 1, score, rating, visited);
    search(grid, r, c + 1, m, n, target + 1, score, rating, visited);
    search(grid, r, c - 1, m, n, target + 1, score, rating, visited);
}

void solveDay10()
{
    using namespace std;

    const auto lines = getInputLines("../input/day10.input");

    vector<vector<int>> grid(lines.size());
    for (int i = 0; i < lines.size(); ++i) {
        grid[i].resize(lines[i].size());
        for (int j = 0; j < lines[i].size(); ++j) {
            grid[i][j] = lines[i][j] - '0';
        }
    }

    const int m = grid.size();
    const int n = grid.front().size();

    int totalScore = 0;
    int totalRating = 0;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] != 0) {
                continue;
            }

            set<pair<int, int>> visited;
            int score = 0;
            int rating = 0;

            search(grid, r, c, m, n, 0, score, rating, visited);

            totalScore += score;
            totalRating += rating;
        }
    }
    cout << "Part 1: " << totalScore << endl;
    cout << "Part 2: " << totalRating << endl;
}
