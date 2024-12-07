#pragma once

#include <string>
#include <vector>

std::vector<std::string> getInputLines(std::string_view filePath);

std::vector<std::vector<int>> parseVectorInt(const std::vector<std::string>& lines,
                                             char seperator = ' ');
