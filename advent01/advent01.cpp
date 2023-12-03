#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <map>
#include <queue>

const int UNINITIALIZED = -1;

const std::string verboseNumbers[] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

void matchNumbers(std::string line) {
    std::string underline = "";
    std::priority_queue<std::pair<int, int>> numbersPositions;
    for (int i = 0; i < line.size(); i++) {
        underline += " ";
    }
    // check for digits
    for (int i = 0; i < 10; i++) {
        int positionFirst = line.find(i + '0');
        int positionLast = line.rfind(i + '0');
        if (positionFirst != line.npos) {
            std::cout << "Found " << i << " on position " << positionFirst << '\n';
            //underline[positionFirst] = '^';
            numbersPositions.push(std::make_pair(i, positionFirst));
        }
        if (positionLast != line.npos && positionFirst != positionLast) {
            std::cout << "Found " << i << " on position " << positionLast << '\n';
            //underline[positionLast] = '^';
            numbersPositions.push(std::make_pair(i, positionLast));
        }
    }
    // check for verbose numbers
    for (int i = 0; i < 10; i++) {
        int positionFirst = line.find(verboseNumbers[i]);
        int positionLast = line.rfind(verboseNumbers[i]);
        if (positionFirst != line.npos) {
            std::cout << "Found " << i << " on position " << positionFirst << '\n';
            //underline[positionFirst] = '^';
            numbersPositions.push(std::make_pair(i, positionFirst));
        }
        if (positionLast != line.npos && positionFirst != positionLast) {
            std::cout << "Found " << i << " on position " << positionLast << '\n';
            //underline[positionLast] = '^';
            numbersPositions.push(std::make_pair(positionLast, i));
        }
    }
    underline[numbersPositions.top().first] = '^';
    int lastIndex = numbersPositions.top().first;
    while (!numbersPositions.empty()) {
        lastIndex = numbersPositions.top().first;
        numbersPositions.pop();
    }
    underline[lastIndex] = '^';
    std::cout << line << '\n' << underline << '\n';
}

int main()
{
    std::vector<int> calibrationValues;
    std::string line;
    std::ifstream file;
    file.open("input.txt");
    if (file.bad()) {
        std::cerr << "File not found\n";
        return -1;
    }
    while (file >> line) {
        /*int first = UNINITIALIZED;
        int last = UNINITIALIZED;
        bool firstReaded = false;
        for (auto character : line) {
            if (character >= '0' && character <= '9') {
                if (firstReaded) {
                    last = character - '0';
                }
                else {
                    first = character - '0';
                    firstReaded = true;
                }
            }
        }
        if (last != UNINITIALIZED)
            calibrationValues.push_back(first * 10 + last);
        else
            calibrationValues.push_back(first * 11);*/
        matchNumbers(line);
    }
    file.close();
    std::cout << "Sum:" << std::accumulate(calibrationValues.begin(), calibrationValues.end(), 0) << '\n';
}