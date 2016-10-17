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
     * Selectes all replacable nodes for the given approximation.
     */
    graph::Nodes selectSuitableNodes(Approximation approximation, graph::GraphPtr graph);
    graph::Nodes selectOperation(graph::GraphPtr graph, std::string op);
    graph::Nodes selectAll(graph::GraphPtr graph);
    
    bool isOperationalNode(graph::NodePtr node);
    bool isLoopIterator(std::string it);
    
    
    /**
     * Checks if there exists nodes on which the approximation can be applied.
     */
    bool canBeApplied(Approximation approximation, graph::GraphPtr graph);

    /**
     * Replaces the second operand in the first node, the operation of both nodes.
     * The first operation/node is intended to be as support in order to calculate the right value for the second operation.
     * To achieve this as output of the first node 'tmp' is set and also as first operand of the second node.
     * replacement      list of two nodes to be adjusted.
     * op1              string representing the new operation of the first node.
     * op2              string representing the operation of the second node.
     * operand          string representing new the operand.
     */
    void replaceOperations(graph::Nodes &replacement, std::string op1, std::string op2, std::string operand);
    /**
     * Perform the same operation as above but changing the operands that above are left unchanged.
     */
    void invertedReplaceOperations(graph::Nodes &replacement, std::string op1, std::string op2, std::string operand);

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
     * Returns the shift to be applied accordingly to a probability distribution given by
     * the previous applied shifts.
     */
    int calculateShift();
    std::vector<int> getShiftList();
    void fillBaseShiftValue(std::map<int, int> &shifts);

    /**
     * Evolves the shift by adding a single bit in a random position.
     */
    int evolveShift(int shift);

    extern std::vector<Approximation> approximations;
    extern std::map<Approximation, std::string> approximationsOp;

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