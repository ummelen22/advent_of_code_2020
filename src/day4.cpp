#include <iostream>
#include <vector>
#include <map>
#include <fstream>

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

std::vector<std::map<std::string, std::string>> readPuzzleInputFromFile(std::string fileName) {
    std::ifstream inFile(fileName);
    std::string line;
    std::vector<std::map<std::string, std::string>> passports{};

    std::map<std::string, std::string> passport{};

    while (getline(inFile, line)) {
        if (line.empty()) {
            passports.push_back(passport);
            passport.clear();
            break;
        }
        std::vector<std::string> passportData = splitString(line, " ");
        for (const auto& data : passportData) {
            std::vector<std::string> keyValuePair = splitString(data, ":");
            passport.insert(std::pair<std::string, std::string>(keyValuePair[0], keyValuePair[1]));
        }
    }

    for (auto& passport : passports) {
        for (auto& m : passport) {
            std::cout << m.first << "-" << m.second << std::endl;
        }
    }

    return passports;
}

int main() {
    readPuzzleInputFromFile("../inputs/day4.txt");
    return 0;
}