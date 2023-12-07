#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

int getHandRank(const std::string &hand) {
    std::map<char, int> cardsMap;
    std::vector<std::pair<char, int>> cardsCount;
    for (auto c: hand) {
        cardsMap[c]++;
    }
    cardsCount.reserve(cardsMap.size());
    for (auto item: cardsMap) {
        cardsCount.emplace_back(item);
    }
    std::sort(cardsCount.begin(), cardsCount.end(), [](std::pair<char, int> &p1, std::pair<char, int> &p2) {
        return p2.second < p1.second;
    });
    for (auto pair: cardsCount) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }
    // calculate hand rank
    if (cardsCount[0].second == 5)
        return 7;
    if (cardsCount[0].second == 4)
        return 6;
    if (cardsCount[0].second == 3 && cardsCount[1].second == 2)
        return 5;
    if (cardsCount[0].second == 3)
        return 4;
    if (cardsCount[0].second == 2 && cardsCount[1].second == 2)
        return 3;
    if (cardsCount[0].second == 2 && cardsCount[1].second == 2)
        return 2;
    if (cardsCount[0].second == 2)
        return 1;
    return 0;
}

int main() {
    std::ifstream file;
    std::string line;
    int num;
    int sum = 0;
    std::vector<std::pair<std::string, int>> data;
    file.open("input.txt");
    if (!file.good()) {
        std::cerr << "File not found\n";
        return -1;
    }
    while (file >> line) {
        file >> num;
        data.emplace_back(line, num);
    }
    file.close();
    for (const auto &record: data) {
        int rank = getHandRank(record.first);
        std::cout << record.first << ": " << rank << '\n';
        sum += rank * record.second;
    }
    std::cout << "sum: " << sum;
    return 0;
}
