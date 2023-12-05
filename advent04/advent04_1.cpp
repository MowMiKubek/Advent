#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <cmath>
const int BASE_PREFIX_LEN = 10;

std::set<int> splitNumbers(const std::string& text) {
    std::stringstream ss(text);
    std::set<int> numbers;
    int num;
    while(ss >> num) {
        numbers.insert(num);
    }
    return numbers;
}

int main() {
    std::ifstream file;
    std::vector<std::string> cardData;
    std::string line;
    int lineNr = 1;
    file.open("input.txt");
    if(!file.good()) {
        std::cerr << "File not found";
        return -1;
    }
    while(std::getline(file, line)) {
        line = line.erase(0,BASE_PREFIX_LEN);
        cardData.push_back(line);
        ++lineNr;
    }
    file.close();

    int sum = 0;
    for(const auto& cards: cardData) {
        int result = 0;
        int splitIndex = cards.find('|');
        std::string firstCard = cards.substr(0, splitIndex);
        std::string secondCard = cards.substr(splitIndex + 2, cards.length());
        std::set<int> winningCards = splitNumbers(firstCard);
        std::set<int> myCards = splitNumbers(secondCard);
        std::set<int> common;
        std::set_intersection(winningCards.begin(), winningCards.end(), myCards.begin(), myCards.end(), std::inserter(common, common.begin()));
        if(common.size() > 0) {
            result = (int)pow(2,common.size() - 1);
            sum += result;
        }
        std::cout << "Result:" << result << "| ";
        for(auto c: common) {
            std::cout << c << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "Sum: " << sum;
    return 0;
}
