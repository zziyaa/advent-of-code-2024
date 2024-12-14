#include <iostream>
#include <set>

#include "utility.hpp"

using namespace std;

using Grid = vector<string>;

namespace {
vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
} // namespace

bool isInsideGrid(const Grid& grid, const int r, const int c)
{
    return r >= 0 && r < grid.size() && c >= 0 && grid.front().size();
}

bool inSameRegion(const Grid& grid, const pair<int, int>& curr, const pair<int, int>& other)
{
    if (!isInsideGrid(grid, other.first, other.second) ||
        grid[curr.first][curr.second] != grid[other.first][other.second]) {
        return false;
    }
    return true;
}

void exploreRegion(const Grid& grid, const int r, const int c, uint64_t& area, uint64_t& perimeter,
                   uint64_t& sides, set<pair<int, int>>& visited)
{
    area++;
    visited.insert({r, c});

    // Find corners (i.e., sides) by checking pairs of neighbors.
    for (int i = 0; i < directions.size(); ++i) {
        const auto dir1 = directions[i];
        const auto dir2 = directions[(i + 1) % directions.size()];

        const auto curr = make_pair(r, c);
        const auto plot1 = make_pair(r + dir1.first, c + dir1.second);
        const auto plot2 = make_pair(r + dir2.first, c + dir2.second);

        if (!inSameRegion(grid, curr, plot1) && !inSameRegion(grid, curr, plot2)) {
            sides++;
        }
        else if (inSameRegion(grid, curr, plot1) && inSameRegion(grid, curr, plot2)) {
            // Both neighbors are in the same region, check the diagonal node
            const auto plot3 =
                make_pair(r + dir1.first + dir2.first, c + dir1.second + dir2.second);

            if (!inSameRegion(grid, curr, plot3)) {
                sides++;
            }
        }
    }

    // Continue to explore with unvisited neighbors in the same region
    for (const auto& dir : directions) {
        const auto curr = make_pair(r, c);
        const auto other = make_pair(r + dir.first, c + dir.second);

        if (!inSameRegion(grid, curr, other)) {
            perimeter++;
        }
        else if (!visited.count(other)) {
            exploreRegion(grid, other.first, other.second, area, perimeter, sides, visited);
        }
    }
}

void solveDay12()
{
    using namespace std;

    const auto grid = getInputLines("../input/day12.input");

    const int m = grid.size();
    const int n = grid.front().size();

    uint64_t totalCost = 0;
    uint64_t totalCostSide = 0;
    set<pair<int, int>> visited;

    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (visited.count(make_pair(r, c))) {
                continue;
            }

            uint64_t area = 0;
            uint64_t perimeter = 0;
            uint64_t sides = 0;

            exploreRegion(grid, r, c, area, perimeter, sides, visited);

            totalCost += area * perimeter;
            totalCostSide += area * sides;
        }
    }

    cout << "Part 1: " << totalCost << endl;
    cout << "Part 2: " << totalCostSide << endl;
}
