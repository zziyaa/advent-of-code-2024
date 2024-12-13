#include <iostream>
#include <sstream>

#include "utility.hpp"

void solveDay11()
{
    using namespace std;

    const auto input = getInputLines("../input/day11.input").front();
    unordered_map<uint64_t, uint64_t> nums;

    istringstream iss(input);
    string token;
    while (iss >> token) {
        nums[stoull(token)]++;
    }

    constexpr auto blinkCount = 75;

    for (int i = 0; i < blinkCount; ++i) {
        unordered_map<uint64_t, uint64_t> newNums;

        for (auto it = nums.begin(); it != nums.end(); it++) {
            auto num = it->first;
            auto count = it->second;

            if (num == 0) {
                newNums[1] += count;
            }
            else if (auto numStr = to_string(num); numStr.size() % 2 == 0) {
                auto num1 = numStr.substr(0, numStr.size() / 2);
                auto num2 = numStr.substr(numStr.size() / 2, numStr.size() / 2);

                newNums[stoull(num1)] += count;
                newNums[stoull(num2)] += count;
            }
            else {
                newNums[num * 2024] += count;
            }
        }

        nums = newNums;
    }

    uint64_t totalCount = 0;
    for (auto it = nums.begin(); it != nums.end(); it++) {
        totalCount += it->second;
    }
    if (blinkCount == 25) {
        cout << "Part 1: " << totalCount << endl;
    }
    else if (blinkCount == 75) {
        cout << "Part 2: " << totalCount << endl;
    }
}
