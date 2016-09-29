#ifndef EXECUTER_H
#define EXECUTER_H


#include <string>
#include "graph.h"


namespace executer {

    double runGraph(graph::GraphPtr graph);
    double runabacusApproximation(graph::GraphPtr graph);

    void runNode(graph::NodePtr node, graph::GraphPtr graph);


    bool isControlOp(std::string op);
    bool isNumber(const std::string &str);


    template<typename T>
    void extractOperand(std::string name, T &op, graph::GraphPtr graph)
    {
        if (isNumber(name)){
            op = std::stod(name, NULL);
        } else {
            graph->get(name, op);
        }
    }

    template<typename T>
    void getOperands(std::string nameOp1, T &op1, std::string nameOp2, T &op2, graph::GraphPtr graph) 
    {
        extractOperand(nameOp1, op1, graph);
        extractOperand(nameOp2, op2, graph);
    }

    template<typename T>
    T sum(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 + op2;
    }

    template<typename T>
    T minus(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 - op2;
    }

    template<typename T>
    T mult(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 * op2;
    }

    template<typename T>
    T div(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 / op2;
    }

    template<typename T>
    T leftShift(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        long int *ptr = (long int *) (&op1);
        *ptr <<= (int) op2;
        return (T) *ptr;
    }

    template<typename T>
    T rightShift(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        long int *ptr = (long int *) (&op1);
        *ptr >>= (int) op2;
        return (T) *ptr;
    }

    template<typename T>
    T less(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 < op2;
    }

    template<typename T>
    T lessEq(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 <= op2;
    }

    template<typename T>
    T eq(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 == op2;
    }

    template<typename T>
    T greatEq(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 >= op2;
    }

    template<typename T>
    T great(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 >= op2;
    }

    template<typename T>
    T diff(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 != op2;
    }

    template<typename T>
    T andBin(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 && op2;
    }

    template<typename T>
    T orBin(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return op1 || op2;
    }
    // from here
    template<typename T>
    T andBit(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        long int *ptr1 = (long int *) (&op1);
        long int *ptr2 = (long int *) (&op2);
        return (T) (*ptr1 & *ptr2);
    }

    template<typename T>
    T orBit(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        long int *ptr1 = (long int *) (&op1);
        long int *ptr2 = (long int *) (&op2);
        return (T) (*ptr1 | *ptr2);
    }

    template<typename T>
    T negBit(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op;
        extractOperand(nameOp1, op, graph);
        long int *ptr = (long int *) (&op);
        return (T) ~(*ptr);
    }

    template<typename T>
    T cast(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return (T) op2;
    }

    template<typename T>
    void selectOperation(graph::NodePtr node, graph::GraphPtr graph)
    {
        T out;
        T (*operation)(std::string, std::string, graph::GraphPtr);

        if (node->op.compare("+") == 0) {
            operation = &sum<T>;
        } else if(node->op.compare("-") == 0) {
            operation = &minus<T>;
        } else if(node->op.compare("*") == 0) {
            operation = &mult<T>;
        } else if(node->op.compare("/") == 0) {
            operation = &div<T>;
        } else if(node->op.compare("<<") == 0) {
            operation = &leftShift<T>;
        } else if(node->op.compare(">>") == 0) {
            operation = &rightShift<T>;
        } else if(node->op.compare("<") == 0) {
            operation = &less<T>;
        } else if(node->op.compare("<=") == 0) {
            operation = &lessEq<T>;
        } else if(node->op.compare("==") == 0) {
            operation = &eq<T>;
        } else if(node->op.compare(">=") == 0) {
            operation = &greatEq<T>;
        } else if(node->op.compare(">") == 0) {
            operation = &great<T>;
        } else if(node->op.compare("!=") == 0) {
            operation = &diff<T>;
        } else if(node->op.compare("&&") == 0) {
            operation = &andBin<T>;
        } else if(node->op.compare("||") == 0) {
            operation = &orBin<T>;
        } else if(node->op.compare("&") == 0) {
            operation = &andBit<T>;
        } else if(node->op.compare("|") == 0) {
            operation = &orBit<T>;
        } else if(node->op.compare("~") == 0) {
            operation = &negBit<T>;
        } else if(node->op.compare("<<c") == 0) {
            operation = &cast<T>;
        }

        out = operation(node->incoming[0], node->incoming[1], graph);

        graph->set(node->out, out);
    }


}


#endif /* EXECUTER_H */