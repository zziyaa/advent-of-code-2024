#include "utility.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::vector<std::string> getInputLines(std::string_view filePath)
{
    using namespace std;

    vector<string> lines;

    ifstream ifs(filePath);
    if (!ifs.is_open()) {
        std::cerr << "Unable to open the file for reading\n";
        return lines;
    }

    string line;
    while (getline(ifs, line)) {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::vector<int>> parseVectorInt(const std::vector<std::string>& lines, char seperator)
{
    using namespace std;

    vector<vector<int>> result(lines.size());

    for (int i = 0; i < lines.size(); ++i) {
        const auto& line = lines[i];
        istringstream iss(line);
        string token;
        vector<int> nums;
        while (getline(iss, token, seperator)) {
            nums.push_back(stoi(token));
        }
        result[i] = nums;
    }

    return result;
}
