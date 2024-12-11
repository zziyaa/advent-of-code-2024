#include <iostream>
#include <string>

#include "utility.hpp"

uint64_t calculateChecksum(const std::vector<std::string>& data)
{
    uint64_t checksum = 0;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i] == ".") {
            continue;
        }
        checksum += i * stoi(data[i]);
    }
    return checksum;
}

void solveDay9()
{
    using namespace std;

    // slice is a pair of index and length
    using slice = pair<int, int>;

    const auto diskMap = getInputLines("../input/day9.input").front();

    /* *** Preprocessing the input *** */

    int id = -1;
    vector<string> data;
    vector<slice> freeSpaces;
    vector<pair<int, slice>> files; // id -> slice

    for (int i = 0; i < diskMap.size(); ++i) {
        const bool isFreeSpace = (i % 2) == 1;
        const int count = diskMap[i] - '0';
        const slice currSpan = make_pair(data.size(), count);

        string toBeAppended;
        if (isFreeSpace) {
            toBeAppended = ".";
            freeSpaces.push_back(currSpan);
        }
        else {
            ++id;
            toBeAppended = to_string(id);
            files.push_back(make_pair(id, currSpan));
        }

        for (int j = 0; j < count; ++j) {
            data.push_back(toBeAppended);
        }
    }

    /* *** Part 1 *** */

    auto dataCopy = data;

    int l = 0;
    int r = dataCopy.size() - 1;

    while (l < r) {
        while (l < r && dataCopy[l] != ".") {
            ++l;
        }

        while (l < r && dataCopy[r] == ".") {
            --r;
        }

        if (l >= r) {
            break;
        }

        swap(dataCopy[l++], dataCopy[r--]);
    }

    cout << "Part 1: " << calculateChecksum(dataCopy) << endl;

    /* *** Part 2 *** */

    for (auto it = files.rbegin(); it != files.rend(); it++) {
        int index = it->second.first;
        const int len = it->second.second;

        for (auto& freeSpace : freeSpaces) {
            auto& freeSpaceIndex = freeSpace.first;
            auto& freeSpaceLen = freeSpace.second;

            if (freeSpaceLen < len || freeSpaceIndex >= index) {
                continue;
            }

            for (int i = 0; i < len; ++i) {
                swap(data[freeSpaceIndex++], data[index++]);
            }
            freeSpaceLen -= len;
            break;
        }
    }

    cout << "Part 2: " << calculateChecksum(data) << endl;
}