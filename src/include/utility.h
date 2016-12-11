#ifndef UTILITY_H
#define UTILITY_H

#include <climits>
#include <cstdlib>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "node.h"

bool is(std::string a, std::string b);
bool isNumber(std::string &str);
bool containsNumber(std::string &str);
bool isOpEmpty(graph::NodePtr node);

template <typename T, typename E> inline
bool isIn(std::map<T, E> &m, T key)
{
    return m.find(key) != m.end();
}

template <typename T, typename E> inline
bool isIn(std::set<T, E> &m, T key)
{
    return m.find(key) != m.end();
}

std::vector<std::string> split(const std::string &s, char delim);

std::vector<int> getPowTwo();

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

long int getMask(std::string type);
long int leftshift(long int a, long int b);
long int rightshift(long int a, long int b);
long int andbit(long int a, long int b);
long int orbit(long int a, long int b);


#endif /* UTILITY_H */