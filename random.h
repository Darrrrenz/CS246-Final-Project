#ifndef RANDOM_H
#define RANDOM_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class Random{
    private:
    long unsigned int seed;
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    public:
    Random(long unsigned int seed):seed{seed}{};
    ~Random();
    int generate();
    int generateTypeII();
    std::vector<int> generateTypeIII();
    int generateTypeIV(int size);
    std::vector<int> generateTypeV(int size);
    int generateTypeVI();
};
#endif
