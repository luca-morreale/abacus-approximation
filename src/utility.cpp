#include "include/utility.h"


bool is(std::string a, std::string b)
{
    return a.compare(b) == 0;
}

bool isNumber(std::string &str)
{
    return !str.empty() && str.find_first_not_of(".0123456789") == std::string::npos;
}

bool isOpEmpty(graph::NodePtr node)
{
    return node->op.size() == 0;
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

