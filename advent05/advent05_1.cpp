#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <sstream>
#include <iterator>
#include <algorithm>

typedef unsigned long long int uint;
typedef std::vector<std::tuple<uint, uint, uint>> tupleVector;

uint lookupMap(tupleVector &lookupTable, int value) {
    for(auto line: lookupTable) {
        int source = std::get<1>(line);
        int target = std::get<0>(line);
        int range = std::get<2>(line);
        if(source <= value && value < source + range) {
            return target + value - source;
        }
    }
    return value;
}

int main() {
    std::ifstream file;
    std::string filenames[] = {"seed.txt", "soil.txt", "fertilizer.txt", "water.txt", "light.txt", "temperature.txt", "humidity.txt"};
    std::vector<tupleVector> data;
    std::string line;
    int a;
    file.open("input.txt");
    if(!file.good()) {
        std::cerr << "Input file not found: ";
        return -1;
    }
    std::vector<uint> seeds;
    while(file >> a) seeds.push_back(a);
    file.close();
    for(int i=0; i<=6; i++) {
        file.open("data/" + filenames[i]);
        if(!file.good()) {
            std::cerr << "File not found: " << filenames[i];
            return -1;
        }
        tupleVector segment;
        while(std::getline(file, line)) {
            std::istringstream ss(line);
            uint a, b, c;
            ss >> a >> b >> c;
            segment.push_back(std::make_tuple(a, b, c));
        }
        data.push_back(segment);
        file.close();
    }
    for(int step=0; step <= 6; step++) {
        for(int seedId = 0; seedId < seeds.size(); seedId++) {
            seeds[seedId] = lookupMap(data[step], seeds[seedId]);
        }
    }
    std::copy(seeds.begin(), seeds.end(), std::ostream_iterator<uint>(std::cout, "\n"));
    std::cout << "Min value: " << *std::min_element(seeds.begin(), seeds.end());
    return 0;

}
