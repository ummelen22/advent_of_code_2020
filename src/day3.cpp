#include <iostream>
#include <vector>
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

struct Slope {
    int dx;
    int dy;
};

int numberOfTreesOnSlope(const std::vector<std::string>& area, const Slope slope){
    int index = 0;
    int counter = 0;
    int stepRight = slope.dx;
    int stepDown = slope.dy;
    for (std::vector<std::string>::const_iterator it = area.begin(); it != area.end() + stepDown - 1; it += stepDown) {
            if ((*it)[index % (*it).length()] == '#') {
                counter++;
            }
            index += stepRight;
        }
    return counter;
}

int productOfTreesOnSlopes(const std::vector<std::string>& inputLines, const std::vector<Slope>& slopes) {
    int product = 1;
    for (const auto& slope : slopes) {
        product *= numberOfTreesOnSlope(inputLines, slope);
    } 
    return product;
}

int main() {
    const std::vector<std::string> inputLines = readPuzzleInputFromFile("../inputs/day3.txt");

    const std::vector<Slope> slopesPart1 = {{3, 1}}; // slopes for part 1 {step right, step down}
    const std::vector<Slope> slopesPart2 = { // slopes for part 2 {step right, step down}
        {1, 1},
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2}
    };
    
    std::cout << "Solution part 1: " << productOfTreesOnSlopes(inputLines, slopesPart1) << std::endl;
    std::cout << "Solution part 2: " << productOfTreesOnSlopes(inputLines, slopesPart2) << std::endl;
}