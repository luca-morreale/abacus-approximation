#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <map>

#include "utility.h"
#include "node.h"
#include "graph.h"
#include "syntax.h"
#include "executer.h"

namespace approximation {

    typedef graph::Nodes (*Approximation)(graph::NodePtr node);

    graph::Nodes selectSuitableNodes(graph::GraphPtr graph, Approximation approximation);
    graph::Nodes selectOperation(graph::GraphPtr graph, std::string op);
    graph::Nodes selectAll(graph::GraphPtr graph);

    graph::Nodes approximateSum(graph::NodePtr node);
    graph::Nodes approximateMinus(graph::NodePtr node);
    graph::Nodes approximateMult(graph::NodePtr node);
    graph::Nodes approximateDiv(graph::NodePtr node);
    graph::Nodes approximateValue(graph::NodePtr node);

    void replaceOperations(graph::Nodes &replacement, std::string op1, std::string op2, std::string operand);
    std::string calculateShift();
    void doubleIncrement(graph::Nodes &replacement);

    extern std::vector<Approximation> approximations;
    extern std::map<Approximation, std::string> approximationsName;

    typedef std::pair<Approximation, std::string> approxpair;

    const Approximation approx_values[] = {
        &approximateSum, &approximateMinus, &approximateMult,
        &approximateDiv, &approximateValue
    };

    const approxpair op_start_values[] = {
        approxpair(&approximateSum, "+"),
        approxpair(&approximateMinus, "-"),
        approxpair(&approximateMult, "*"),
        approxpair(&approximateDiv, "/")
    };

    const size_t map_start_values_size = 5;

    const size_t op_map_values_size = 4;

}

#endif