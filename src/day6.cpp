#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

typedef std::vector<std::string> GroupAnswers;

std::vector<GroupAnswers> readPuzzleInputFromFile(const std::string& fileName) {
    std::ifstream inFile(fileName);
    std::string line;
    GroupAnswers answersPerGroup;
    std::vector<GroupAnswers> answers;
    while(getline(inFile, line)) {
        if(line.empty()) {
            answers.push_back(std::move(answersPerGroup));
            continue;
        }
        answersPerGroup.push_back(std::move(line));
    }
    if (!answersPerGroup.empty()) answers.push_back(std::move(answersPerGroup));
    return answers;
}

size_t numberOfAnswers_AnsweredByAnyGroupMember(const std::vector<std::string>& answers) {
    if ( answers.size() == 1 ) return answers[0].size();
    
    std::string uniqueAnswers = answers[0];
    for (size_t i = 1; i < answers.size(); i++) {
        for (const char& answer : answers[i]) {
            if (uniqueAnswers.find(answer) == std::string::npos) {
                uniqueAnswers += answer;
            }
        }
    }
    return uniqueAnswers.size();
}

size_t numberOfAnswers_AnsweredByAllGroupMembers(const GroupAnswers& answers) {
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
    auto answers = readPuzzleInputFromFile("../inputs/day6.txt");
    size_t sumAny = 0;
    size_t sumAll = 0;
    for (auto& answersPerGroup : answers) {
        sumAny += numberOfAnswers_AnsweredByAnyGroupMember(answersPerGroup);
        sumAll += numberOfAnswers_AnsweredByAllGroupMembers(answersPerGroup);
    }
    std::cout << "Solution part 1: " << sumAny << std::endl;
    std::cout << "Solution part 2: " << sumAll << std::endl;
}
