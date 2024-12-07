#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "utility.hpp"

void solveDay1()
{
    using namespace std;

    const auto lines = getInputLines("../input/day1.input");

    vector<int> leftCol(lines.size());
    vector<int> rightCol(lines.size());

    for (int i = 0; i < lines.size(); ++i) {
        istringstream iss(lines[i]);
        string token;

        iss >> token;
        leftCol[i] = stoi(token);

        iss >> token;
        rightCol[i] = stoi(token);
    }

    sort(leftCol.begin(), leftCol.end());
    sort(rightCol.begin(), rightCol.end());

    uint64_t sumDiff = 0;

    for (int i = 0; i < leftCol.size(); ++i) {
        sumDiff += abs(leftCol[i] - rightCol[i]);
    }

    cout << "Part 1: " << sumDiff << std::endl;

    unordered_map<int, int> frequency;
    for_each(rightCol.cbegin(), rightCol.cend(),
             [&frequency](const auto num) -> void { frequency[num]++; });

    uint64_t similarityScore = 0;

    for (const auto num : leftCol) {
        similarityScore += num * frequency[num];
    }

    cout << "Part 2: " << similarityScore << std::endl;
}
