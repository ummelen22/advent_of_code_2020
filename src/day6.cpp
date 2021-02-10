#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <regex>
#include <algorithm>


std::unordered_map<int, std::vector<std::string>> readPuzzleInputFromFile(std::string fileName) {
    std::ifstream inFile(fileName);
    std::string line;
    std::unordered_map<int, std::vector<std::string>> answers;
    int group = 1;
    while(getline(inFile, line)) {
        if(line.empty()) {
            group++;
            continue;
        }
        if (answers.find(group) != answers.end()) {
            answers[group].push_back(line);
        } else {
            answers.insert(std::pair<int, std::vector<std::string>>(group, { line }));
        }
    }
    return answers;
}

template <typename T>
struct skip {
    T& t;
    std::size_t n;
    skip(T& vec, std::size_t indexToSkip) : t(vec), n(indexToSkip) {}
    auto begin() -> decltype(std::begin(t)) {
        return std::next(std::begin(t), n);
    }
    auto end() -> decltype(std::end(t)) {
        return std::end(t);
    }
};

int numberOfDifferentAnswers(const std::vector<std::string>& answers) {
    if ( answers.size() == 1 ) return answers[0].size();

    std::string uniqueAnswers = answers[0];
    for (auto& answersPerPerson : skip<decltype(answers)>(answers, 1)) {
        for (const char& answer : answersPerPerson) {
            if (uniqueAnswers.find(answer) == std::string::npos) {
                uniqueAnswers += answer;
            }
        }
    }
    return uniqueAnswers.size();
}

// int numberOfDifferentAnswers(const std::vector<std::string>& answers) {

//     if ( answers.size() == 1 ) return answers.size();

//     std::vector<char> uniqueAnswers(answers[0].size());
//     std::cout << "-----" << std::endl;
//     std::cout << answers[0] << std::endl;
//     for (std::size_t i = 0; i < answers[0].size(); ++i) {
//         std::cout << uniqueAnswers[i] << std::endl;
//         uniqueAnswers[i] = answers[0][i];
//         std::cout << uniqueAnswers[i] << std::endl;
//     }
//     for (char& it : uniqueAnswers) {
//         std::cout << it << std::endl;
//     }
//     std::cout << "hi" << std::endl;
//     for (char& uniqueAnswer : uniqueAnswers) {
//         for (const std::string& answer : answers) {
//             if (answer.find(uniqueAnswer) == std::string::npos) {
//                 std::cout << uniqueAnswer << " " << answer << std::endl;
//                 uniqueAnswers.erase(std::find(uniqueAnswers.begin(), uniqueAnswers.end(), uniqueAnswer));
//             }
//         }
//     }
//     std::cout << "3" << std::endl;
    
//     std::cout << "\n\n" << std::endl;
//     return uniqueAnswers.size();
// }

int main() {
    std::unordered_map<int, std::vector<std::string>> answersPerGroup = readPuzzleInputFromFile("../inputs/day6.txt");
    int sum = 0;
    for (auto& group : answersPerGroup) {
        sum += numberOfDifferentAnswers(group.second);
    }
    std::cout << "Solution part 1: " << sum << std::endl;
}
