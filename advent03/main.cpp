#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <map>
#include <set>

bool isSymbol(char c) {
    return c == '*';
}

int checkIfIsPartNumber(std::vector<std::string> &grid, int verticalIdx, int horizontalIdx) {
    const unsigned int horizontalLength = grid[0].size();
    const unsigned int verticalLength = grid.size();

    auto withinBounds = [&](int vIdx, int hIdx) {
        return vIdx >= 0 && vIdx < verticalLength && hIdx >= 0 && hIdx < horizontalLength;
    };

    for (int v = -1; v <= 1; ++v) {
        for (int h = -1; h <= 1; ++h) {
            if (v == 0 && h == 0) continue;
            int newVIdx = verticalIdx + v;
            int newHIdx = horizontalIdx + h;

            if (withinBounds(newVIdx, newHIdx) && isSymbol(grid[newVIdx][newHIdx])) {
                return newVIdx * grid[0].size() + newHIdx;
            }
        }
    }
    return -1;
}

typedef unsigned long int ulong;

int main() {

    std::ifstream file;
    std::vector<std::string> grid;
    std::string line;
    std::map<int, std::pair<ulong, int>> lookupStars;
    file.open("input.txt");
    if (!file.good()) {
        std::cerr << "File not found\n";
        return -1;
    }
    while (file >> line) {
        grid.push_back(line + '.');
    }
    file.close();
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if(grid[i][j] == '*')
                lookupStars[i*grid[0].size() + j] = std::make_pair(1, 0);
        }
    }
    for (int i = 0; i < grid.size(); i++) {
        bool isPartNumber = false;
        std::string textNumber;
        std::set<int> starIndices;
        for (int j = 0; j < grid[i].size(); j++) {
            if (isdigit(grid[i][j])) {
                textNumber += grid[i][j];
                int starIndex = checkIfIsPartNumber(grid, i, j);
                if (starIndex != -1) {
                    isPartNumber = true;
                    starIndices.insert(starIndex);
                    std::cout << "Found value " << textNumber << " pushing index: " << starIndex << '\n';
                }
            } else if (!textNumber.empty()) {
                if (isPartNumber) {
                    std::cout << "saving(" << starIndices.size() << "):";
                    for(auto c: starIndices) {
                        std:: cout << c << ',';
                        auto oldPair = lookupStars[c];
                        ulong oldValue = oldPair.first;
                        int oldCount = oldPair.second;
                        lookupStars[c] = std::make_pair(oldValue * std::stol(textNumber), oldCount + 1);
                    }
                    std::cout << '\n';
                    isPartNumber = false;
                }
                textNumber = "";
            }
        }
    }
    ulong sum = 0;
    for(auto [key, value]: lookupStars) {
        if(value.second == 2){
            std::cout << "Index " << key << "\n";
            std::cout << "value: " << value.first << " count: " << value.second << '\n';
            sum += value.first;
        }
    }
    std::cout << "sum: " << sum << '\n';
    return 0;
}
