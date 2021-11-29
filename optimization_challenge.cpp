#include <vector>
#include <chrono>
#include <random>
#include <iostream>
#include <cstdint>

unsigned int pop_count(uint64_t x, uint64_t y) {
        uint64_t res = x ^ y;
        return __builtin_popcountll (res);
}

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

    // assume v1 and v2 sizes are multiple of 8
    for(int i = 0; i < v1.size()/8; i+=8) {
        const uint64_t a = *(reinterpret_cast<const uint64_t*>(&v1[i]));
        const uint64_t b = *(reinterpret_cast<const uint64_t*>(&v2[i]));
        result += pop_count(a, b);
    }
    return result;
}

int main(void) {

    std::default_random_engine generator;
    std::uniform_real_distribution<unsigned char> distribution(0,255);

    // creating test points
    const unsigned int numPoints = 32 * 1000000;
    std::vector<unsigned char> pointsA;
    pointsA.resize(numPoints);
    for(unsigned char& point: pointsA) {
        point = distribution(generator);
    }

    std::vector<unsigned char> pointsB;
    pointsB.resize(numPoints);
    for(unsigned char& point: pointsB) {
        point = distribution(generator);
    }

    // call the baseline function
    auto start = std::chrono::steady_clock::now();
    auto res_base = dist_baseline(pointsA, pointsB);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> diff = end - start;

    std::cout << "[BASELINE], result = " << res_base << " took " << diff.count() << " seconds " << std::endl;

    start = std::chrono::steady_clock::now();
    auto res_opt = dist_optimized(pointsA, pointsB);
    end = std::chrono::steady_clock::now();
    diff = end - start;

    std::cout << "[OPTIMIZED], result = " << res_opt << " took " << diff.count() << " seconds " << std::endl;
    return 0;
}
