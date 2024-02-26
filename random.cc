#include "random.h"
#include <iostream>

Random::~Random(){}
int Random::generate(){
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
    std::vector<int> v2 = { 1, 2, 3, 4, 5, 6 };
    std::shuffle( v1.begin(), v1.end(), rng );
    std::shuffle( v2.begin(), v2.end(), rng );
    return (v1[0]+v2[0]);
}
int Random::generateTypeII(){
    std::vector<int> v1 = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    std::shuffle(v1.begin(),v1.end(),rng);
    return v1[0];
}

std::vector<int> Random::generateTypeIII(){
    std::vector<int> v = {0, 1, 2, 3, 4};
    std::shuffle(v.begin(),v.end(),rng);
    return v;
}

int Random::generateTypeIV(int size){
    std::vector<int> v(size);
    iota(v.begin(),v.end(),0);
    std::shuffle(v.begin(),v.end(),rng);
    return v.at(0);
}

std::vector<int> Random::generateTypeV(int size){
    std::vector<int> v(size);
    iota(v.begin(),v.end(),0);
    std::shuffle(v.begin(),v.end(),rng);
    return v;
}

int Random::generateTypeVI(){
    std::vector<int> v = {0, 1, 2, 3, 4};
    std::shuffle(v.begin(),v.end(),rng);
    return v.at(0);
}
