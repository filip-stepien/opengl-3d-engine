#include "Random.hpp"

float demo::Random::randomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 generator { rd() };
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(generator);
}

float demo::Random::randomDir() {
    std::random_device rd;
    std::mt19937 generator { rd() };
    std::uniform_int_distribution<> distrib(0, 1);
    return distrib(generator) ? 1.0f : -1.0f;
}
