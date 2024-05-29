#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace demo {
    class Random {
    public:
        static float randomFloat(float min, float max);
        static int randomInt(int min, int max);
        static float randomDir();
    };
}

#endif