#include <iostream>
#include <set>

#include "utility.hpp"

using Grid = std::vector<std::string>;
using Pos = std::pair<int, int>;

static bool isPositionInsideGrid(const Grid& grid, const Pos pos)
{
    return pos.first >= 0 && pos.first < grid.size() && pos.second >= 0 &&
           pos.second < grid.front().size();
}

void solveDay8()
{
    using namespace std;

    /* *** Preprocessing *** */

    const auto grid = getInputLines("../input/day8.input");

    const auto m = grid.size();
    const auto n = grid.front().size();

    unordered_map<char, vector<Pos>> antennaPositions;

    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] == '.') {
                continue;
            }
            antennaPositions[grid[r][c]].push_back(make_pair(r, c));
        }
    }

    /* *** Part 1 *** */

    set<Pos> antinodePositions;

    for (auto it = antennaPositions.cbegin(); it != antennaPositions.cend(); it++) {
        const auto& positions = it->second;
        for (int i = 0; i < positions.size() - 1; ++i) {
            for (int j = i + 1; j < positions.size(); ++j) {
                const auto p1 = positions[i];
                const auto p2 = positions[j];

                const auto diffX = p1.second - p2.second;
                const auto diffY = p1.first - p2.first;

                auto antinodeX = p1.second + diffX;
                auto antinodeY = p1.first + diffY;
                auto newAntinode = make_pair(antinodeY, antinodeX);
                if (isPositionInsideGrid(grid, newAntinode)) {
                    antinodePositions.insert(newAntinode);
                }

                antinodeX = p2.second - diffX;
                antinodeY = p2.first - diffY;
                newAntinode = make_pair(antinodeY, antinodeX);
                if (isPositionInsideGrid(grid, newAntinode)) {
                    antinodePositions.insert(newAntinode);
                }
            }
        }
    }
    cout << "Part 1: " << antinodePositions.size() << endl;

    /* *** Part 2 *** */

    antinodePositions.clear();

    for (auto it = antennaPositions.cbegin(); it != antennaPositions.cend(); it++) {
        const auto& positions = it->second;
        for (int i = 0; i < positions.size() - 1; ++i) {
            for (int j = i + 1; j < positions.size(); ++j) {
                const auto p1 = positions[i];
                const auto p2 = positions[j];

                const auto diffX = p1.second - p2.second;
                const auto diffY = p1.first - p2.first;

                antinodePositions.insert(p1);
                antinodePositions.insert(p2);

                // p1 -> p2
                auto antinodeX = p1.second + diffX;
                auto antinodeY = p1.first + diffY;
                auto newAntinode = make_pair(antinodeY, antinodeX);

                while (isPositionInsideGrid(grid, newAntinode)) {
                    antinodePositions.insert(newAntinode);

                    antinodeX += diffX;
                    antinodeY += diffY;
                    newAntinode = make_pair(antinodeY, antinodeX);
                }

                // p2 -> p1
                antinodeX = p2.second - diffX;
                antinodeY = p2.first - diffY;
                newAntinode = make_pair(antinodeY, antinodeX);

                while (isPositionInsideGrid(grid, newAntinode)) {
                    antinodePositions.insert(newAntinode);

                    antinodeX -= diffX;
                    antinodeY -= diffY;
                    newAntinode = make_pair(antinodeY, antinodeX);
                }
            }
        }
    }
    cout << "Part 2: " << antinodePositions.size() << endl;
}
