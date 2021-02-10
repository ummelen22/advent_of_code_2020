#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <limits.h>

std::vector<std::string> readPuzzleInputFromFile(std::string fileName) {
    std::ifstream inFile(fileName);
    std::string line;
    std::vector<std::string> linesInFile;

    while (getline(inFile, line)) {
        linesInFile.push_back(line);
    }
    return linesInFile;
}

std::string seatingToBinary(std::string seating) {
    std::string binary = "";
    for (char const& it : seating) {
        if (it == 'F' || it == 'L') {
            binary += "0";
        } else if (it == 'B' || it == 'R') {
            binary += "1";
        }
    }
    return binary;
}

int binaryToDecimal(std::string binary){
    try {
        return std::stoi(binary, nullptr, 2);
    } catch (std::invalid_argument) {
        std::cout << "Binary: " << binary << " could not be converted to a decimal\n";
        return 0;
    }
}

int main() {
    // Read puzzle input from txt file
    std::string fileName = "../inputs/day5.txt";
    std::vector<std::string> inputArray = readPuzzleInputFromFile(fileName);
    std::map<int, std::vector<int>> rowCol{};
    int maxSeat = 0;
    for (std::string& seating : inputArray) {
        std::string binarySeat = seatingToBinary(seating);
        int row = binaryToDecimal(binarySeat.substr(0, 7));
        int col = binaryToDecimal(binarySeat.substr(7, 10));
        if (rowCol.find(row) != rowCol.end()) {
            rowCol[row].push_back(col);
        } else {
            rowCol.insert(std::pair<int, std::vector<int>>(row, {col}));
        }

        int seat = row * 8 + col;
        if (seat > maxSeat) maxSeat = seat;
    }

    int seat[2] = {0, 0};
    int sum = 0;
    for (auto& it : rowCol) {
        if (it.second.size() == 7 && it.first != rowCol.begin()->first && it.first != rowCol.end()->first) {
            for (auto& itCol : it.second) {
                sum += itCol;
            }
            seat[0] = it.first;
            seat[1] = 28 - sum;
            break;
        }
    }
    int mySeat = seat[0] * 8 + seat[1];

    std::cout << "Solution Part 1: " << maxSeat << std::endl;
    std::cout << "Solution Part 2: " << mySeat << std::endl;
    return 0;
}
