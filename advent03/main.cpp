#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

bool isSymbol(char c) {
    return !isdigit(c) && c != '.';
}

bool checkIfIsPartNumber(std::vector<std::string> &grid, int verticalIdx, int horizontalIdx) {
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
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::ifstream file;
    std::vector<std::string> grid;
    std::string line;
    int sum = 0;
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
        bool isPartNumber = false;
        std::string textNumber;
        for (int j = 0; j < grid[i].size(); j++) {
            if (isdigit(grid[i][j])) {
                textNumber += grid[i][j];
                if (checkIfIsPartNumber(grid, i, j))
                    isPartNumber = true;
            } else if (!textNumber.empty()) {
                if (isPartNumber) {
//                    std::cout << textNumber << ' ';
                    sum += std::stoi(textNumber);
                    isPartNumber = false;
                }
                textNumber = "";
            }
        }
        if (!textNumber.empty() && isPartNumber) {
            std::cout << textNumber << ' ';
            sum += std::stoi(textNumber);
        }
//        std::cout << '\n';
    }
    std::cout << "Suma: " << sum;
    return 0;
}
