#include "Random.hpp"

float demo::Random::randomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 generator { rd() };
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(generator);
}

int demo::Random::randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 generator { rd() };
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(generator);
}

float demo::Random::randomDir() {
    return randomInt(0, 1) ? 1.0f : -1.0f;
}
