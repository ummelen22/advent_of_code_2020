#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <regex>

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

std::vector<std::unordered_map<std::string, std::string>> readPuzzleInputFromFile(std::string fileName) {
    std::ifstream inFile(fileName);
    std::string line;
    std::vector<std::unordered_map<std::string, std::string>> passports{};

    std::unordered_map<std::string, std::string> passport{};

    while (getline(inFile, line)) {
        if (line.empty()) {
            passports.push_back(passport);
            passport.clear();
            continue;
        }
        std::vector<std::string> passportData = splitString(line, " ");
        for (const auto& data : passportData) {
            std::vector<std::string> keyValuePair = splitString(data, ":");
            passport.insert(std::pair<std::string, std::string>(keyValuePair[0], keyValuePair[1]));
        }
    }
    passports.push_back(passport);

    return passports;
}

bool endsWith(std::string fullString, std::string ending) {
    if (fullString.length() >= ending.length()) {
        return (fullString.compare(fullString.length() - ending.length(), ending.length(), ending) == 0);
    } else {
        return false;
    }
}

bool isKeyValueValid(std::string key, std::string value){
    if (key.find("yr") != std::string::npos) {
        try { // Validate years
            int yr = std::stoi(value);
            if (key == "byr" && yr >= 1920 && yr <= 2002) return true;
            if (key == "iyr" && yr >= 2010 && yr <= 2020) return true;
            if (key == "eyr" && yr >= 2020 && yr <= 2030) return true;
        }
        catch (std::invalid_argument) {
            std::cout << "Value " << value << " for key " << key << " could not be converted to int.\n";
        }
    } else if (key == "hgt" ) {
        // std::cout << value << std::endl;
        std::string heightString = value;
        try {
            if (endsWith(value, "cm")) {
                heightString.erase(heightString.length() - 2, 2);
                int height = std::stoi(heightString);
                if (height >= 150 && height <= 193) return true;
            } else if (endsWith(value, "in")){
                heightString.erase(heightString.length() - 2, 2);
                int height = std::stoi(heightString);
                if (height >= 59 && height <= 76) return true;
            } else return false;
        } catch (std::invalid_argument) {
            std::cout << "Value " << value << " for key " << key << " could not be converted to int.\n";
        }
    } else if (key == "hcl") {
        const std::regex hairColorConstraints("^#([a-f0-9]{6})$"); 
        std::cout << value << " " << std::regex_match(value, hairColorConstraints) << std::endl;
    }
    return false;
}

int main() {
    std::vector<std::unordered_map<std::string, std::string>> passports = readPuzzleInputFromFile("../inputs/day4.txt");
    std::vector<std::string> keys = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    int counter = passports.size();
    for (const auto& passport : passports) {
        for (const auto& key : keys) {
            if (passport.find(key) == passport.end()) {
                counter--;
                break;
            } 
            else if (key == "hgt" ) counter -= (int)!isKeyValueValid(key, passport.at(key));
        }
    }

    std::cout << "Solution part 1: " << counter << std::endl;
}