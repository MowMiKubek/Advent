#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

const int MAX_REPETITIONS = 100;

int main() {
    std::ifstream file;
    std::string line;
    std::vector<std::vector<int>> data;
    file.open("input.txt");
    if (!file.good()) {
        std::cerr << "File not found";
        return -1;
    }
    while (std::getline(file,line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        int num;
        while (ss >> num)
            row.emplace_back(num);
        data.emplace_back(row);
    }
    file.close();
    long long int sum = 0;
    for(const auto& current: data) {
        std::vector<std::vector<int>> differences;
        differences.push_back(current);
        for (int i = 0; i < MAX_REPETITIONS; i++) {
            auto vector = *differences.rbegin();
            // check for zeros
            bool allZeros = true;
            for (auto a: vector) {
                if (a != 0)
                    allZeros = false;
            }
            if (allZeros)
                break;
            // calculate differences
            std::vector<int> newRow;
            newRow.reserve(vector.size() - 1);
            for (int j = 0; j < vector.size() - 1; j++) {
                newRow.emplace_back(vector[j + 1] - vector[j]);
            }
            differences.push_back(newRow);
        }
        int value = 0;
        for(int i=differences.size()-1; i >= 0; i--) {
            value = *differences[i].begin() - value;
        }
        sum += value;
    }
    std::cout << "Sum: " << sum << '\n';
    return 0;
}
