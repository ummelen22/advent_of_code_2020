#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>


std::vector<std::string> readPuzzleInputFromFile(std::string fileName) {
    std::ifstream inFile(fileName);
    std::string line;
    std::vector<std::string> linesInFile;

    while (getline(inFile, line)) {
        linesInFile.push_back(line);
    }
    return linesInFile;
}

int numberOfTreesOnSlope(const std::vector<std::string>& area, std::vector<int> slope){
    int index = 0;
    int counter = 0;
    int stepRight = slope[0];
    int stepDown = slope[1];
    for (std::vector<std::string>::const_iterator it = area.begin(); it != area.end() + stepDown - 1; it += stepDown) {
            if ((*it)[index % (*it).length()] == '#') {
                counter++;
            }
            index += stepRight;
        }
    return counter;
}

int productOfTreesOnSlopes(const std::vector<std::string>& inputLines, const std::vector<std::vector<int>>& stepCombinations) {
    
    std::vector<int> numberOfTreesPerSlope = {};

    for (std::vector<std::vector<int>>::const_iterator it = stepCombinations.begin(); it != stepCombinations.end(); it++) {
        int numberOfTrees = numberOfTreesOnSlope(inputLines, *it);
        numberOfTreesPerSlope.push_back(numberOfTrees);
    } 

    int product = 1;
    for (auto& numberOfTrees : numberOfTreesPerSlope){
        product *= numberOfTrees;
    }

    return product;
}

int main() {
    std::vector<std::string> inputLines = readPuzzleInputFromFile("../inputs/day3.txt");

    std::vector< std::vector<int> > slopesPart1 = {{3, 1}}; // slopes for part 1 {step right, step down}
    std::vector< std::vector<int> > slopesPart2 = { // slopes for part 2 {step right, step down}
        {1, 1},
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2}
    };
    
    std::cout << "Solution part 1: " << productOfTreesOnSlopes(inputLines, slopesPart1) << std::endl;
    std::cout << "Solution part 2: " << productOfTreesOnSlopes(inputLines, slopesPart2) << std::endl;
}