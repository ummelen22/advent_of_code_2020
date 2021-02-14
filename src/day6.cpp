#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


std::vector<std::vector<std::string>> readPuzzleInputFromFile(const std::string& fileName) {
    std::ifstream inFile(fileName);
    std::string line;
    std::vector<std::string> answersPerGroup;
    std::vector<std::vector<std::string>> answers;
    while(getline(inFile, line)) {
        if(line.empty()) {
            answers.push_back(answersPerGroup);
            answersPerGroup.clear();
            continue;
        }
        answersPerGroup.push_back(line);
    }
    if (!answersPerGroup.empty()) answers.push_back(answersPerGroup);
    return answers;
}

template <typename T>
struct Skip {
    T& t;
    std::size_t n;
    Skip(T& vec, std::size_t startIndex) : t(vec), n(startIndex) {}
    auto begin() -> decltype(std::begin(t)) {
        return std::next(std::begin(t), n);
    }
    auto end() -> decltype(std::end(t)) {
        return std::end(t);
    }
};

int numberOfAnswers_AnsweredByAnyGroupMember(const std::vector<std::string>& answers) {
    if ( answers.size() == 1 ) return answers[0].size();

    std::string uniqueAnswers = answers[0];
    for (auto& answersPerPerson : Skip<decltype(answers)>(answers, 1)) {
        for (const char& answer : answersPerPerson) {
            if (uniqueAnswers.find(answer) == std::string::npos) {
                uniqueAnswers += answer;
            }
        }
    }
    return uniqueAnswers.size();
}

int numberOfAnswers_AnsweredByAllGroupMembers(const std::vector<std::string>& answers) {
    if ( answers.size() == 1 ) return answers[0].size();
    
    std::vector<char> allAnswered(answers[0].begin(), answers[0].end());
    for (std::vector<char>::const_iterator it = allAnswered.begin(); it < allAnswered.end(); it++) {
        for (const std::string& answersPerPerson : answers)
        {
            if (answersPerPerson.find(*it) == std::string::npos)
            {
                allAnswered.erase(it);
                it--;
                if (allAnswered.empty()) return 0;   
                break;
            }
        }
    }
    return allAnswered.size();
}

int main() {
    std::vector<std::vector<std::string>> answers = readPuzzleInputFromFile("../inputs/day6.txt");
    int sumAny, sumAll = 0;
    for (auto& answersPerGroup : answers) {
        sumAny += numberOfAnswers_AnsweredByAnyGroupMember(answersPerGroup);
        sumAll += numberOfAnswers_AnsweredByAllGroupMembers(answersPerGroup);
    }
    std::cout << "Solution part 1: " << sumAny << std::endl;
    std::cout << "Solution part 2: " << sumAll << std::endl;
}
