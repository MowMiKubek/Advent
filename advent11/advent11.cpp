#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream file;
    std::string line;
    std::vector<std::string> grid;
    file.open("input.txt");
    if (!file.good()) {
        std::cerr << "File not found\n";
        return -1;
    }
    while (file >> line) {
        grid.emplace_back(line);
    }
    file.close();
    // extend horizontal axis
   for (int i = 0; i < grid[0].size(); i++) {
       bool empty = true;
       for (int j = 0; j < grid.size() && empty; j++) {
           if (grid[j][i] != '.')
               empty = false;
       }
       if (empty) {
           for (auto &j: grid) {
               j.insert(j.begin() + i, 1, '.');
           }
           i++;
       }
   }
   // extend vertical axis
   for (int i = 0; i < grid.size(); i++) {
       bool empty = true;
       for (int j = 0; j < grid[0].size() && empty; j++) {
           if (grid[i][j] != '.')
               empty = false;
       }
       if (empty) {
           std::string copy = grid[i];
           grid.insert(grid.begin() + i, copy);
           i++;
       }
   }
    std::vector<std::pair<int, int>> starIndexes;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '#')
                starIndexes.emplace_back(i, j);
        }
    }
    int sum = 0;
    for (int i = 0; i < starIndexes.size(); i++) {
        for (int j = i+1; j < starIndexes.size(); j++) {
            auto star1 = starIndexes[i];
            auto star2 = starIndexes[j];
            int vertical = std::abs(star1.first - star2.first);
            int horizontal = std::abs(star1.second - star2.second);
            int value = vertical + horizontal;
            sum += value;
        }
    }
    std::cout << "Sum: " << sum;
    return 0;
}
