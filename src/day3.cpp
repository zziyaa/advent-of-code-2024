#include "utility.hpp"

#include <cctype>
#include <iostream>
#include <regex>
#include <sstream>

int multiply(const std::string& s)
{
    // Assumes that the `s` is in the following format: "mul(<num>,<num>)"

    std::istringstream iss(s);
    std::string token;

    std::getline(iss, token, '(');
    std::getline(iss, token, ',');
    const auto operand1 = std::stoi(token);

    std::getline(iss, token, ')');
    const auto operand2 = std::stoi(token);

    return operand1 * operand2;
}

void solveDay3()
{
    const auto lines = getInputLines("../input/day3.input");

    uint64_t sum = 0;
    uint64_t enabledSum = 0;

    auto enabled = true;

    std::regex r("(do\\(\\)|don't\\(\\)|mul\\([0-9]{1,3},[0-9]{1,3}\\))");

    for (const auto& line : lines) {
        auto it = std::sregex_iterator(line.cbegin(), line.cend(), r);
        while (it != std::sregex_iterator()) {
            const auto found = it->str();
            if (found == "do()") {
                enabled = true;
            }
            else if (found == "don't()") {
                enabled = false;
            }
            else {
                const auto result = multiply(it->str());
                sum += result;
                if (enabled) {
                    enabledSum += result;
                }
            }
            it++;
        }
    }

    std::cout << "Part 1: " << sum << std::endl;
    std::cout << "Part 2: " << enabledSum << std::endl;
}
