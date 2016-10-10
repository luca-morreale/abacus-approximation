#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <map>
#include <string>
#include <vector>

#include "node.h"

bool is(std::string a, std::string b);
bool isNumber(std::string &str);
bool isOpEmpty(graph::NodePtr node);

std::vector<double> normalizeProbabilities(std::vector<int> &prob);
double* normalizeProbabilities(int prob[], size_t size);


int sampleIndex(std::vector<double> &probabilities);
int sampleIndex(double probabilities[], size_t size);

double randDouble();


template <typename T>
T selectUniformlyRandom(std::vector<T> array)
{
    int index = rand() % array.size();
    return array[index];
}

template <typename T, typename E>
std::vector<E> values(std::map<T, E> m)
{
    std::vector<E> v;
    for(auto it = m.begin(); it != m.end(); ++it) {
        v.push_back(it->second);
    }
    return v;
}

template <typename T, typename E>
std::vector<T> keys(std::map<T, E> m)
{
    std::vector<T> v;
    for(auto it = m.begin(); it != m.end(); ++it) {
        v.push_back(it->first);
    }
    return v;
}


#endif /* UTILITY_H */