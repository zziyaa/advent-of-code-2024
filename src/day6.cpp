#include <iostream>
#include <set>

#include "utility.hpp"

namespace {
enum class Direction {
    eUp = 0,
    eRight,
    eDown,
    eLeft
};
} // namespace

using Grid = std::vector<std::string>;
using Pos = std::pair<int, int>; // Position in the grid: (x, y)

bool isPositionInsideGrid(const Grid& grid, const Pos pos)
{
    const auto i = pos.first;
    const auto j = pos.second;

    return i >= 0 && i < grid.size() && j >= 0 && j < grid.front().size();
}

Pos getNextPosition(const Grid& grid, const Pos curr, const Direction dir)
{
    switch (dir) {
    case Direction::eUp:
        return std::make_pair(curr.first - 1, curr.second);
    case Direction::eRight:
        return std::make_pair(curr.first, curr.second + 1);
    case Direction::eDown:
        return std::make_pair(curr.first + 1, curr.second);
    case Direction::eLeft:
        return std::make_pair(curr.first, curr.second - 1);
    default:
        return {};
    }
}

Direction turnRight(const Direction dir)
{
    switch (dir) {
    case Direction::eUp:
        return Direction::eRight;
    case Direction::eRight:
        return Direction::eDown;
    case Direction::eDown:
        return Direction::eLeft;
    case Direction::eLeft:
        return Direction::eUp;
    default:
        return Direction::eUp;
    }
}

void solveDay6()
{
    using namespace std;

    auto grid = getInputLines("../input/day6.input");

    const auto m = grid.size();
    const auto n = grid.front().size();

    Direction dir = Direction::eUp;

    Pos startPos{};
    Pos currPos{};

    set<Pos> obstructions;

    // Find the starting point and obstructions
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] == '#') {
                obstructions.insert(make_pair(r, c));
            }
            else if (grid[r][c] == '^') {
                startPos = make_pair(r, c);
            }
        }
    }

    auto count = 0;
    currPos = startPos;

    while (true) {
        const auto i = currPos.first;
        const auto j = currPos.second;

        // Mark the current position as visited
        if (grid[i][j] != 'x') {
            grid[i][j] = 'x';
            ++count;
        }

        auto nextPos = getNextPosition(grid, currPos, dir);

        while (obstructions.count(nextPos)) {
            dir = turnRight(dir);
            nextPos = getNextPosition(grid, currPos, dir);
        }

        if (!isPositionInsideGrid(grid, nextPos)) {
            // Left the lab
            break;
        }

        // Move forward
        currPos = nextPos;
    }

    cout << "Part 1: " << count << endl;

    auto loopCount = 0;

    auto isGuardInLoop = [](const Grid& grid, const set<Pos>& obstructions, Pos currPos) -> bool {
        Direction dir = Direction::eUp;
        std::set<pair<Pos, Direction>> visited;

        while (true) {
            auto nextPos = getNextPosition(grid, currPos, dir);

            while (obstructions.count(nextPos)) {
                // Did the guard encounter this obstruction before coming from the same direction?
                auto v = make_pair(currPos, dir);
                if (visited.count(v)) {
                    return true;
                }

                visited.insert(v);

                dir = turnRight(dir);
                nextPos = getNextPosition(grid, currPos, dir);
            }

            if (!isPositionInsideGrid(grid, nextPos)) {
                break;
            }

            currPos = nextPos;
        }

        return false;
    };

    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] == 'x' && make_pair(r, c) != startPos) {
                auto newObstructions = obstructions;
                newObstructions.insert(make_pair(r, c));

                if (isGuardInLoop(grid, newObstructions, startPos)) {
                    ++loopCount;
                }
            }
        }
    }

    cout << "Part 2: " << loopCount << endl;
}
