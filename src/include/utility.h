#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include "node.h"

bool is(std::string a, std::string b);
bool isNumber(std::string &str);
bool isOpEmpty(graph::NodePtr node);

std::vector<double> normalizeProbabilities(std::vector<int> &prob);


#endif /* UTILITY_H */