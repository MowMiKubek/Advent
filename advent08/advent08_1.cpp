#include <iostream>
#include <fstream>
#include <map>

const int MAX_REPETITIONS = 100;

int main() {
    std::map<std::string, std::pair<std::string, std::string>> graph;
    std::string directions;
    std::ifstream file;
    std::string line;
    file.open("input.txt");
    if(!file.good()) {
        std::cerr << "File not found";
        return -1;
    }
    std::getline(file, directions);
    std::getline(file, line);
    while(std::getline(file, line)) {
        std::string key = line.substr(0, 3);
        std::string left = line.substr(7, 3);
        std::string right = line.substr(12, 3);
        graph[key] = std::make_pair(left, right);
//        std::cout << "[" << key << "] " << left << ' ' << right << '\n';
    }
    file.close();
    std::string currentNode = "AAA";
    int length = 0;
    for(int i=0; i< MAX_REPETITIONS; i++) {
        for(auto direction: directions) {
//            std::cout << currentNode << ' ' << length << '\n';
//            std::cout << "Step: " << direction << '\n';
            if(direction == 'L')
                currentNode = graph[currentNode].first;
            if(direction == 'R')
                currentNode = graph[currentNode].second;
            length++;
            if(currentNode == "ZZZ") {
                std::cout << "Length: " << length << '\n';
                return 0;
            }
        }
    }
    std::cerr << "Failed to find path in given repetitions limit: " << MAX_REPETITIONS;
    return 0;
}
