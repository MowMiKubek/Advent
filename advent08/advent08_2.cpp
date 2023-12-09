#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <numeric>

const int MAX_REPETITIONS = 10000;

int NWD(int a, int b) {
    int pom;
    while (b != 0) {
        pom = b;
        b = a % b;
        a = pom;
    }
    return a;
}

int NWW(int a, int b) {
    return a * b / NWD(a,b);
}

int main() {
    std::map<std::string, std::pair<std::string, std::string>> graph;
    std::string directions;
    std::vector<std::string> startingPositions;
    std::vector<int> results;
    std::ifstream file;
    std::string line;
    file.open("input.txt");
    if (!file.good()) {
        std::cerr << "File not found";
        return -1;
    }
    std::getline(file, directions);
    std::getline(file, line);
    std::cout << "Starting positions:\n";
    while (std::getline(file, line)) {
        std::string key = line.substr(0, 3);
        std::string left = line.substr(7, 3);
        std::string right = line.substr(12, 3);
        graph[key] = std::make_pair(left, right);
        if (key[2] == 'A') {
            startingPositions.emplace_back(key);
            std::cout << key << '\n';
        }
    }
    file.close();
//    results.reserve(startingPositions.size());
//    std::string currentNode = "AAA";
    int length = 0;
    bool searching;
    for (auto currentNode: startingPositions) {
        searching = true;
        for(int i=0; i< MAX_REPETITIONS && searching; i++) {
            for (auto direction: directions) {
                if (direction == 'L')
                    currentNode = graph[currentNode].first;
                if (direction == 'R')
                    currentNode = graph[currentNode].second;
                length++;
                if (currentNode[2] == 'Z') {
                    results.push_back(length);
                    length = 0;
                    searching = false;
                    break;
                }
            }
        }
    }
    for (auto num: results) {
        std::cout << num << ' ';
    }
    std::cout << '\n';
    int result = std::accumulate(results.begin(), results.end(), 1, [](int acc, int value){
        return NWW(acc, value);
    });
    std::cout << "Result: " << result;
    return 0;
}
