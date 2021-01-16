#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> readPuzzleInputFromFile(string &fileName)
{
    ifstream inFile;
    string line;
    vector<int> numbersInFile;

    inFile.open(fileName);
    while (getline(inFile, line))
    {
        numbersInFile.push_back(stoi(line));
    }
    inFile.close();

    return numbersInFile;
}

int getProductOfKeysThatSumUpToX(map<int, int> &inputMap, int &sum, int &numberOfKeys)
{
    for (auto const &it : inputMap)
    {
        int diff = sum - it.first;
        if (numberOfKeys > 2) {
            // Create temporary map to prevent the same key to be found in the recursive function call
            map<int, int> tmpInputMap = inputMap;
            tmpInputMap.erase(it.first);
            int tmpNumberOfKeys = numberOfKeys - 1;
            if (int product = getProductOfKeysThatSumUpToX(tmpInputMap, diff, tmpNumberOfKeys))
            {
                return it.first * product;
            }
            else
            {
                continue;
            }
        }
        auto search = inputMap.find(diff);
        if (search != inputMap.end() and search->second != it.second)
        {
            return it.first * search->first;
        }
    }
    // No 2 keys found that sum up to diff
    return 0;
}

int main()
{
    // Read puzzle input from txt file
    string fileName = "../inputs/day1.txt";
    vector<int> inputArray = readPuzzleInputFromFile(fileName);

    // Create std::map, mapping the puzzle input integers to their indices (O(log n) time complexity for search)
    map<int, int> inputMap;
    for (int i = 0; i < inputArray.size(); i++)
    {
        inputMap[inputArray[i]] = i;
    }

    // Get user input
    int sum;
    int numberOfKeys;
    cout << "Sum you are looking for: ";
    cin >> sum;
    cout << "Amount of numbers that should add up to " << sum << ": ";
    cin >> numberOfKeys;

    // Find product of keys recursively
    int product = getProductOfKeysThatSumUpToX(inputMap, sum, numberOfKeys);
    cout << "Solution: " << product << endl;
}