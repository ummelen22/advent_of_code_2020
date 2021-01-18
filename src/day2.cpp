#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

using namespace std;

vector<string> readPuzzleInputFromFile(string &fileName) {
    ifstream inFile;
    string line;
    vector<string> linesInFile;

    inFile.open(fileName);
    while (getline(inFile, line)) {
        linesInFile.push_back(line);
    }
    inFile.close();

    return linesInFile;
}

struct Bounds {
    // Contains the lower and upper bound of how often a letter should be in the password
    int bounds[2];
};

map<string, map<char, Bounds>> splitStrings(vector<string>& linesInFile) {
    size_t pos = 0;
    string subString;
    string delimiter = " ";
    map<string, map<char, Bounds>> result;
    for (auto &line : linesInFile) {
        vector<string> subStrings;
        while ((pos = line.find(delimiter)) != string::npos) {
            subString = line.substr(0, pos);
            subStrings.push_back(subString);
            line.erase(0, pos + delimiter.length());
        }
        subStrings.push_back(line);

        string boundsString = subStrings.front();
        char letter = subStrings[1][0];
        string password = subStrings.back();
        while (result.find(password) != result.end()) {
            password += "_";
        }
        string boundsDelimiter = "-";
        auto pos = boundsString.find(boundsDelimiter);
        int lb = stoi(boundsString.substr(0, pos));
        int ub = stoi(boundsString.substr(pos+boundsDelimiter.length(), string::npos));

        Bounds bounds = {lb, ub};

        map<char, Bounds> tmp;
        tmp.insert(pair<char, Bounds>(letter, bounds));
        result.insert(pair<string, map<char, Bounds>>(password, tmp));
    }
    return result;
}

int howOftenCharInString(char& c, string& s) {
    int n = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            n++;
        }
    }
    return n;
}

bool isPasswordValid(string password, char letter, int bounds[2]) {
    int numberOfOccurrences = howOftenCharInString(letter, password);
    int lb = min(bounds[0], bounds[1]);
    int ub = max(bounds[0], bounds[1]);
    if (numberOfOccurrences >= lb && numberOfOccurrences <= ub) {
        return true;
    } else {
        return false;
    }
}

int main() {
    // Read puzzle input from txt file
    string fileName = "../inputs/day2.txt";
    vector<string> inputLines = readPuzzleInputFromFile(fileName);
    map<string, map<char, Bounds>> passwordMap = splitStrings(inputLines);

    int numberOfValidPasswords = 0;
    for (auto &itr : passwordMap){
        for (auto &ptr : itr.second) {
            if (isPasswordValid(itr.first, ptr.first, ptr.second.bounds)) {
                    numberOfValidPasswords++;
                }
        }
    }
    cout << "Solution: " << numberOfValidPasswords << endl;
}