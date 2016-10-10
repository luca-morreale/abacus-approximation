#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <map>

#include "graph.h"
#include "node.h"
#include "syntax.h"
#include "utility.h"

namespace approximation {

    typedef graph::Nodes (*Approximation)(graph::NodePtr node, int &mask);

    /**
     * Generates the approximated nodes with respect to the one given.
     * Sum is replaced with OR bitwise.
     * Sub is replaced with AND bitwise between the first operand and the second one negated.
     * Multiplication is replaced with a shift and a sum.
     * Division is replaced with a shift and a subtraction
     * Value approximation can cut of some bits from any operation.
     */
    graph::Nodes approximateSum(graph::NodePtr node, int &mask);
    graph::Nodes approximateMinus(graph::NodePtr node, int &mask);
    graph::Nodes approximateMult(graph::NodePtr node, int &mask);
    graph::Nodes approximateDiv(graph::NodePtr node, int &mask);
    graph::Nodes approximateValue(graph::NodePtr node, int &mask);

    /**
     * Selectes all replacable nodes for the given approximation.
     */
    graph::Nodes selectSuitableNodes(graph::GraphPtr graph, Approximation approximation);
    graph::Nodes selectOperation(graph::GraphPtr graph, std::string op);
    graph::Nodes selectAll(graph::GraphPtr graph);

    void replaceOperations(graph::Nodes &replacement, std::string op1, std::string op2, std::string operand);
    int calculateShift();
    std::vector<int> getShiftList();
    void fillBaseShiftValue(std::map<int, int> &shifts);
    int evolveShift(int shift);

    extern std::vector<Approximation> approximations;
    extern std::map<Approximation, std::string> approximationsName;

    typedef std::pair<Approximation, std::string> approxpair;

    /**
     * Arrays used to populate the above map and vector.
     */
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