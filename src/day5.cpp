#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
    
    int max_seat = 0;
    for (std::string& seating : inputArray) {
        std::string binarySeat = seatingToBinary(seating);
        int row = binaryToDecimal(binarySeat.substr(0, 7));
        int col = binaryToDecimal(binarySeat.substr(7, 10));

        int seat = row * 8 + col;

        if (seat > max_seat) max_seat = seat;
    }
    std::cout << "Solution Part 1: " << max_seat << std::endl;
    return 0;
}