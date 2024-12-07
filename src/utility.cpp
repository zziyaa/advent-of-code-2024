#include "utility.hpp"

#include <fstream>
#include <iostream>
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
