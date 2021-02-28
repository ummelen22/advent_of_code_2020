#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>

// Puzzle input file
const std::string INPUT = "../inputs/test.txt";

typedef std::unordered_map<std::string, int> BagContents;

/*
 * Struct to define a bag and its contents
 */
struct Bag
{
    std::string bag_type;
    BagContents bag_contents;

    // human readable print of the bag and its contents
    void print()
    {
        std::cout << bag_type << " bag contains:\n";
        if (!bag_contents.empty())
        {
            for (auto& content : bag_contents)
            {
                std::cout << "\t * " << content.second << " " << content.first << " bag(s)\n";
            }
        }
        else
        {
            std::cout << "\t * no other bags\n";
        }
        std::cout << "\n";
    }
};

/*
 * Parses contents of a bag from a string and stores them in an unordered set
 */
BagContents parseBagContentsFromString(const std::string& s)
{
    std::regex rgx("bag[s]?[,.][ ]?");
    std::regex no_other("no other");
    std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;

    // Define bag contents, i.e., how many of which bag type is contained
    BagContents contents;
    std::string bag_type;
    int amount;
    while (iter != end)
    {
        std::string content = *iter;
        if (std::regex_search(content, no_other))
        {
            break;
        }
        try
        {
            bag_type = content.substr(2, content.length() - 3);
            amount = std::stoi(content.substr(0, 1));
        }
        catch (const std::invalid_argument& ia)
        {
            std::cout << ia.what() << ": " << *iter << " couldn't be converted to an integer\n";
            exit(1);
        }
        contents.insert(std::pair<std::string, int>(bag_type, amount));
        ++iter;
    }

    return contents;
}

/*
 * Parses a bag and its contents from a string
 * Assumes string of the following format: "<bag_type> bags contain <bag_contents>"
 */
Bag parseBagFromString(const std::string& s)
{
    std::string substring_to_find = "bags contain";
    std::string bag_type = s.substr(0, s.find(substring_to_find) - 1);
    std::string contents_string =
        s.substr(s.find(substring_to_find) + substring_to_find.length() + 1, s.length());
    auto bag_contents = parseBagContentsFromString(contents_string);
    Bag bag = {bag_type, bag_contents};
    return bag;
}

/*
 * Parses all bags and their contents from the puzzle input file
 */
std::vector<Bag> readPuzzleInputFromFile(const std::string& fileName)
{
    std::vector<Bag> bags;
    std::ifstream inFile(fileName);
    std::string line;
    while (getline(inFile, line))
    {
        bags.push_back(parseBagFromString(std::move(line)));
    }

    for (auto& bag : bags)
    {
        bag.print();
    }

    return bags;
}

int main() { std::vector<Bag> bags = readPuzzleInputFromFile(INPUT); }
