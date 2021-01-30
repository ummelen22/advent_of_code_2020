#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <regex>
#include <algorithm>

std::vector<std::string> splitString(std::string line, std::string delimiter){
    size_t pos = line.find(delimiter);
    size_t initPos = 0;
    std::vector<std::string> subStrings = {};
    while (pos != std::string::npos) {
        subStrings.push_back(line.substr(initPos, pos - initPos));
        initPos = pos + 1;
        pos = line.find(delimiter, initPos);
    }
    subStrings.push_back(line.substr(initPos, std::min(pos, line.size()) - initPos + 1));

    return subStrings;
}

// std::vector<std::unordered_map<std::string, std::string>> readPuzzleInputFromFile(std::string fileName) {
//     std::ifstream inFile(fileName);
//     std::string line;
//     std::vector<std::unordered_map<std::string, std::string>> passports{};

//     std::unordered_map<std::string, std::string> passport{};

//     while (getline(inFile, line)) {
//         if (line.empty()) {
//             passports.push_back(passport);
//             passport.clear();
//             continue;
//         }
//         std::vector<std::string> passportData = splitString(line, " ");
//         for (const auto& data : passportData) {
//             std::vector<std::string> keyValuePair = splitString(data, ":");
//             passport.insert(std::pair<std::string, std::string>(keyValuePair[0], keyValuePair[1]));
//         }
//     }
//     passports.push_back(passport);

//     return passports;
// }