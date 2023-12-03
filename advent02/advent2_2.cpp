#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <numeric>

const int BASE_LINE_LEN = 8;

const char SET_DELIMITER = ';';
const char DICE_DELIMITER = ',';

std::map<std::string, int> MAX_DICES = {
        {"red", 12},
        {"green", 13},
        {"blue", 14},
};

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> splitByDelimiter(const std::string& text, const char delimiter) {
    std::vector<std::string> words;
    std::stringstream ss(text);
    std::string word;
    while(std::getline(ss, word, delimiter)) {
        words.push_back(trim(word));
    }
    return words;
}

std::pair<std::string, int> getDiceInfo(const std::string& dice) {
    std::string stringNumber = dice.substr(0, dice.find(' '));
    std::string diceColor = dice.substr(dice.find(' ') + 1);
    return std::make_pair(diceColor, std::stoi(stringNumber));
}

int main() {
    std::ifstream file;
    std::string line;
    int sum = 0;
    int lineNr = 1;
    file.open("input.txt");
    if(!file.good()) {
        std::cerr << "File not found\n";
        exit(-1);
    }
    while(std::getline(file, line)) {
        std::map<std::string, int> dicesNumbers = {{"red", 0},{"blue", 0},{"green", 0}};
        unsigned int offset = std::to_string(lineNr).length() - 1;
        std::string truncatedLine = line.substr(BASE_LINE_LEN + offset);
        std::vector<std::string> sets = splitByDelimiter(truncatedLine, SET_DELIMITER);
        std::cout << "Game " << lineNr  << ":\n";
        for(const auto& set: sets) {
            std::vector<std::string> dices = splitByDelimiter(set, DICE_DELIMITER);
            for(const auto& dice: dices) {
                auto diceInfo = getDiceInfo(dice);
                dicesNumbers[diceInfo.first] = std::max(dicesNumbers[diceInfo.first], diceInfo.second);
//                std::cout << "[" << diceInfo.first << "]: " << diceInfo.second << ' ';
            }
        }
        for(auto [key, value]: dicesNumbers) {
            std::cout << "[" << key << "]: " << value << ' ';
        }
        std::cout << '\n';
        int power = std::accumulate(dicesNumbers.begin(), dicesNumbers.end(), 1, [](const int acc, std::pair<std::string, int> p){
            return acc * p.second;
        });
        std::cout << power << '\n';
        sum += power;
        lineNr++;
    }
    std::cout << "Result: " << std::to_string(sum);
    file.close();
    return 0;
}
