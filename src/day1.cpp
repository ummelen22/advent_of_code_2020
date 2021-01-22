#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

std::vector<int> readPuzzleInputFromFile(const std::string &fileName) {
    std::ifstream inFile(fileName);
    std::string line;
    std::vector<int> numbersInFile;

    while (getline(inFile, line)) {
        try {
            numbersInFile.push_back(stoi(line));
        } 
        catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid argument: " << line << " couldn't be converted to an int." << std::endl;
        }
        catch (const std::out_of_range& oor) {
            std::cerr << "Invalid argument: " << line << " is out of range of representable values of int." << std::endl;
        }
    }
    return numbersInFile;
}

int getProductOfKeysThatSumUpToX(std::map<int, int> &inputMap, int &sum, int &numberOfKeys) {
    for (auto const &it : inputMap) {
        int diff = sum - it.first;
        if (numberOfKeys > 2) {
            // Create temporary map to prevent the same key to be found in the recursive function call
            std::map<int, int> tmpInputMap = inputMap;
            tmpInputMap.erase(it.first);
            int tmpNumberOfKeys = numberOfKeys - 1;
            if (int product = getProductOfKeysThatSumUpToX(tmpInputMap, diff, tmpNumberOfKeys)) {
                return it.first * product;
            }
            else {
                continue;
            }
        }
        auto search = inputMap.find(diff);
        if (search != inputMap.end() and search->second != it.second) {
            return it.first * search->first;
        }
    }
    // No 2 keys found that sum up to diff
    return 0;
}

int main() {
    // Read puzzle input from txt file
    std::string fileName = "../inputs/day1.txt";
    std::vector<int> inputArray = readPuzzleInputFromFile(fileName);

    // Create std::map, mapping the puzzle input integers to their indices (O(log n) time complexity for search)
    std::map<int, int> inputMap;
    for (int i = 0; i < inputArray.size(); i++) {
        inputMap[inputArray[i]] = i;
    }

    // Get user input
    int sum;
    int numberOfKeys;
    std::cout << "Sum you are looking for: ";
    std::cin >> sum;
    std::cout << "Amount of numbers that should add up to " << sum << ": ";
    std::cin >> numberOfKeys;

    // Find product of keys recursively
    int product = getProductOfKeysThatSumUpToX(inputMap, sum, numberOfKeys);
    std::cout << "Solution: " << product << std::endl;
}