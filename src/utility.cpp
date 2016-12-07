#include "include/utility.h"
#include <iostream>


bool is(std::string a, std::string b)
{
    return a.compare(b) == 0;
}

bool isNumber(std::string &str)
{
    return !str.empty() && str.find_first_not_of(".0123456789") == std::string::npos;
}

bool containsNumber(std::string &str)
{
    return str.find_first_of("0123456789") != std::string::npos;
}

bool isOpEmpty(graph::NodePtr node)
{
    return node->op.size() == 0;
}

std::vector<std::string> split(const std::string &s, char delim) 
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

std::vector<int> getPowTwo()
{
    std::vector<int> v;
    v.push_back(0);

    for(int i = 0; i < 15; i++) {
        v.push_back(1 << i);
    }

    return v;
}

std::vector<double> normalizeProbabilities(std::vector<int> &prob)
{
    std::vector<double> arr(prob.begin(), prob.end());
    double sum = 0;
    for(auto it = prob.begin(); it != prob.end(); it++) {
        sum += *it;
    }

    for(auto it = arr.begin(); it != arr.end(); it++) {
        *it = *it / sum;
    }

    return arr;
}

double* normalizeProbabilities(int prob[], size_t size)
{
    double *arr = (double *) malloc(sizeof(double) * size);
    
    double sum = 0;
    for(int i = 0; i < size; i++) {
        sum += prob[i];
    }

    for(int i = 0; i < size; i++) {
        arr[i] = prob[i] / sum;
    }

    return arr;
}

int sampleIndex(std::vector<double> &probabilities)
{
    double rnd = randDouble();
    for(int i = 0; i < probabilities.size(); i++) {
        if(rnd < probabilities[i]) {
            return i;
        }
        rnd -= probabilities[i];
    }
}

int sampleIndex(double probabilities[], size_t size)
{
    double rnd = randDouble();
    for(int i = 0; i < size; i++) {
        if(rnd < probabilities[i]) {
            return i;
        }
        rnd -= probabilities[i];
    }
}

double randDouble()
{
    return ((double) rand() / (RAND_MAX));
}
