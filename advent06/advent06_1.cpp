#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

typedef std::pair<double, double> pairInt;

pairInt getWinningRange(int time, int distance) {
    double delta = time*time - 4*distance;
    if(delta < 0) {
        std::cerr << "Unsolvable equation " << time << ' ' << distance << '\n';
        return std::make_pair(0, 0);
    }
    double deltaSqrt = sqrt(delta);
    double t1 = (time - deltaSqrt)/2;
    double t2 = (time + deltaSqrt)/2;
    // check if function is 0 for given value
    auto quadratic = [time, distance](double arg) {
        return -arg*arg + time*arg - distance;
    };
    if(quadratic(t1) == 0)
        t1++;
    if(quadratic(t2) == 0)
        t2--;
    return std::make_pair(ceil(t1), floor(t2));

}

int main() {
    std::vector<int> times{53,91,67,68};
    std::vector<int> distances{250,1330,1081,1025};
    std::vector<pairInt> results;
    results.reserve(times.size());
for(int i=0; i<times.size(); i++) {
        results.push_back(getWinningRange(times[i], distances[i]));
    }
    for(auto result: results) {
        std::cout << "[" << result.first << ';' << result.second << "]\n";
    }
    int result = std::accumulate(results.begin(), results.end(), 1, [](int acc, pairInt current) {
        return acc * (current.second - current.first + 1);
    });
    std::cout << "Result: " << result;
    return 0;
}
