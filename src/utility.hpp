#pragma once

#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> getInputLines(std::string_view filePath);

template <typename T>
void printVector(const std::vector<T>& vec)
{
    std::cout << std::endl;
    for (const auto& v : vec) {
        std::cout << v << std::endl;
    }
}
