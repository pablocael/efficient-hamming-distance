#include <vector>
#include <chrono>
#include <random>
#include <iostream>

// This is the linear naive implementation used as baseline for the optimization benchmark
unsigned int dist_baseline(const std::vector<unsigned char>& v1, const std::vector<unsigned char>& v2) {

    unsigned int result = 0;

    for(int i = 0; i < v1.size(); ++i) {
        result += static_cast<unsigned int>(v1[i] != v2[i]);
    }
    return result;
}

unsigned int dist_optimized(const std::vector<unsigned char>& v1, const std::vector<unsigned char>& v2) {

    unsigned int result = 0;

    for(int i = 0; i < v1.size(); ++i) {
        result += static_cast<unsigned int>(v1[i] != v2[i]);
    }
    return result;
}

int main(void) {

    std::default_random_engine generator;
    std::uniform_real_distribution<unsigned char> distribution(0,255);

    // creating test points
    const unsigned int numPoints = 4e5;
    std::vector<unsigned char> points;
    points.resize(numPoints);
    for(unsigned char& point: points) {
        point = distribution(generator);
    }

    // call the baseline function
    auto start = std::chrono::steady_clock::now();
    dist_baseline(points, points);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> diff = end - start;

    std::cout << "[BASELINE] took " << diff.count() << " seconds " << std::endl;

    start = std::chrono::steady_clock::now();
    dist_optimized(points, points);
    end = std::chrono::steady_clock::now();
    diff = end - start;

    std::cout << "[OPTIMIZED] took " << diff.count() << " seconds " << std::endl;
    return 0;
}
