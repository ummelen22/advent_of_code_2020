#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>


std::vector<std::string> readPuzzleInputFromFile(std::string fileName) {
    std::ifstream inFile(fileName);
    std::string line;
    std::vector<std::string> linesInFile;

    while (getline(inFile, line)) {
        linesInFile.push_back(line);
    }
    return linesInFile;
}

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

struct Bounds {
    // Contains the lower and upper bound of how often a letter should be in the password
    int bounds[2];
};

std::multimap<std::string, std::map<char, Bounds>> createMapFromInput(std::vector<std::string> linesInFile) {
    std::multimap<std::string, std::map<char, Bounds>> inputMap;
    for (auto &line : linesInFile) {
        std::vector<std::string> subStrings = splitString(line, " ");

        // Define bounds, character and password from substrings vector
        std::string boundsString = subStrings.front();
        char letter = subStrings[1][0];
        std::string password = subStrings.back();

        // Extract bounds as integers from boundsString
        try {
            auto pos = boundsString.find('-');
            int lb = std::stoi(boundsString.substr(0, pos));
            int ub = std::stoi(boundsString.substr(pos + 1, std::string::npos));
            Bounds bounds = {lb, ub};

            std::map<char, Bounds> letterBounds = { {letter, bounds} };
            inputMap.insert(std::pair<std::string, std::map<char, Bounds>>(password, letterBounds));
        }   
        catch (const std::invalid_argument &ia) {
            std::cout << "Could not convert one or more bounds in [" << boundsString << "] to integer\n";
            std::cout << "Skipping line " << inputMap.size() + 1 << " of the input file.\n";
            continue; 
        }
    }
    return inputMap;
}

int howOftenCharInString(char c, std::string s) {
    int n = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            n++;
        }
    }
    return n;
}

bool isPasswordValid(std::string password, char letter, int bounds[2], int part) {
    int lb = std::min(bounds[0], bounds[1]); // lower bound
    int ub = std::max(bounds[0], bounds[1]); // upper bound
    if (part == 1) { // Validation method of part 1 of the problem
        int numberOfOccurrences = howOftenCharInString(letter, password);
        if (numberOfOccurrences >= lb && numberOfOccurrences <= ub) {
            return true;
        }
    } else if (part == 2) { // Validation method of part 2 of the problem
        bool firstComparison = password[lb - 1] == letter;
        bool secondComparison = password[ub - 1] == letter;
        if ((firstComparison && !secondComparison) || (!firstComparison && secondComparison)){
            return true;
        }
    } 
    return false;
}

int main() {
    // Read puzzle input from txt file
    std::string fileName = "../inputs/day2.txt";
    std::vector<std::string> inputLines = readPuzzleInputFromFile(fileName);
    std::multimap<std::string, std::map<char, Bounds>> passwordMap = createMapFromInput(inputLines);

    int numberOfValidPasswords[2] = {0, 0};
    for (int part = 1; part <= 2; part++)
        for (auto &itr : passwordMap){
            for (auto &ptr : itr.second) {
                if (isPasswordValid(itr.first, ptr.first, ptr.second.bounds, part)) {
                        numberOfValidPasswords[part-1]++;
                    }
            }
        }
    std::cout << "Solution part 1: " << numberOfValidPasswords[0] << std::endl;
    std::cout << "Solution part 2: " << numberOfValidPasswords[1] << std::endl;
}