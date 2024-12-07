#include "utility.hpp"

#include <iostream>

bool isRecordSafe(const std::vector<int>& record)
{
    auto inc = false;
    auto dec = false;

    for (int i = 0; i < record.size() - 1; ++i) {
        if (record[i] == record[i + 1]) {
            return false;
        }

        if (std::abs(record[i] - record[i + 1]) > 3) {
            return false;
        }

        if (record[i] < record[i + 1]) {
            inc = true;
        }
        else {
            dec = true;
        }

        if (dec && inc) {
            return false;
        }
    }

    return true;
}

bool isRecordSafeWithDeletion(const std::vector<int>& record)
{
    // NOTE: Brute-force solution; can be improved.
    for (int i = 0; i < record.size(); ++i) {
        auto copyRecord(record);
        copyRecord.erase(copyRecord.begin() + i);
        if (isRecordSafe(copyRecord)) {
            return true;
        }
    }
    return false;
}

void solveDay2()
{
    const auto lines = getInputLines("../input/day2.input");
    const auto records = parseVectorInt(lines);

    auto safeRecords = 0;
    auto safeRecordsWithDeletion = 0;

    for (const auto& record : records) {
        if (isRecordSafe(record)) {
            ++safeRecords;
        }
        else if (isRecordSafeWithDeletion(record)) {
            ++safeRecordsWithDeletion;
        }
    }

    std::cout << "Part 1: " << safeRecords << std::endl;
    std::cout << "Part 2: " << safeRecords + safeRecordsWithDeletion << std::endl;
}
