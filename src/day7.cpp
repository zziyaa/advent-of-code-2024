#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#include "utility.hpp"

bool isValid(const uint64_t target, const std::vector<uint64_t>& operands, int index,
             const uint64_t sum, const bool checkConcat = false)
{
    if (sum > target) {
        return false;
    }

    if (index == operands.size()) {
        if (sum == target) {
            return true;
        }
        return false;
    }

    if (isValid(target, operands, index + 1, operands[index] + sum, checkConcat)) {
        return true;
    }

    if (isValid(target, operands, index + 1, operands[index] * sum, checkConcat)) {
        return true;
    }

    if (checkConcat) {
        std::string concat = std::to_string(sum) + std::to_string(operands[index]);

        if (isValid(target, operands, index + 1, std::stoull(concat), true)) {
            return true;
        }
    }

    return false;
}

void solveDay7()
{
    using namespace std;

    /* *** Preprocessing the input *** */

    const auto lines = getInputLines("../input/day7.input");

    vector<uint64_t> targets(lines.size());
    vector<vector<uint64_t>> operands(lines.size());

    for (int i = 0; i < lines.size(); ++i) {
        istringstream iss(lines[i]);
        string token;
        getline(iss, token, ':');
        targets[i] = stoull(token);

        while (iss >> token) {
            operands[i].push_back(stoull(token));
        }
    }

    /* *** Part 1 & 2 *** */

    uint64_t totalSum = 0;
    uint64_t totalSumWithConcat = 0;

    for (int i = 0; i < lines.size(); ++i) {
        if (isValid(targets[i], operands[i], 0, 0)) {
            totalSum += targets[i];
            totalSumWithConcat += targets[i];
        }
        else if (isValid(targets[i], operands[i], 0, 0, true)) {
            totalSumWithConcat += targets[i];
        }
    }

    cout << "Part 1: " << totalSum << endl;
    cout << "Part 2: " << totalSumWithConcat << endl;
}
