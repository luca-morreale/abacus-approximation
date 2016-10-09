#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <string>

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


#endif /* UTILITY_H */