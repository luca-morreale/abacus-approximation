#ifndef BASIC_OPERATIONS_H
#define BASIC_OPERATIONS_H

#include <cstring>

#include "graph.h"
#include "syntax.h"
#include "utility.h"


namespace operations {

    template <typename T> inline
    void extractOperand(std::string name, T &op, graph::GraphPtr graph)
    {
        if (isNumber(name)){
            op = std::stod(name, NULL);
        } else {
            graph->get(syntax::Syntax::getIdentifier(name, graph), op);
        }
    }

    template <> inline
    void extractOperand(std::string name, std::string &op, graph::GraphPtr graph)
    {
        if (isNumber(name)){
            op = std::stod(name, NULL);
        } else {
            graph->get(syntax::Syntax::getIdentifier(name, graph), op);
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


    template <typename T>
    T shiftOperation(T a, T b, long int mask, long int(*operation)(long int, long int)) {
        long int first, second;
        T result;
        std::memcpy(&first, &a, sizeof a);
        std::memcpy(&second, &b, sizeof b);
        operation((first & mask), second);
        first = (first & ~mask) | (((first & mask) >> second) & mask);
        std::memcpy(&result, &first, sizeof first);
        return result;
    }

    template<typename T>
    T leftShift(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return shiftOperation(op1, op2, getMask(graph->getType()), &leftshift);
    }

    template<typename T>
    T rightShift(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return shiftOperation(op1, op2, getMask(graph->getType()), &rightshift);
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

    template <typename T>
    T bitOperation(T a, T b, long int(*operation)(long int, long int)) 
    {
        long int first, second;
        T result;
        std::memcpy(&first, &a, sizeof a);
        std::memcpy(&second, &b, sizeof b);
        first = operation(first, second);
        std::memcpy(&result, &first, sizeof first);
        return result;
    }
    
    template<typename T>
    T andBit(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return bitOperation(op1, op2, &andbit);
    }

    template<typename T>
    T orBit(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return bitOperation(op1, op2, &orbit);
    }


    template<typename T>
    T negBit(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op;
        long int first;

        extractOperand(nameOp1, op, graph);
        
        std::memcpy(&first, &op, sizeof op);
        first = ~first;
        std::memcpy(&op, &first, sizeof first);
        return op;
    }

    template<typename T>
    T cast(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op2;
        extractOperand(nameOp2, op2, graph);

        if(is(nameOp1, "int")) {
            return (int) op2;
        } else if(is(nameOp1, "float")) {
            return (float) op2;
        } else {
            return (double) op2;
        }
    }

    template<typename T>
    T abs(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op;
        extractOperand(nameOp1, op, graph);
        return (T) std::abs((int)op);
    }

    template<typename T>
    void selectOperation(graph::NodePtr node, graph::GraphPtr graph)
    {
        T out;
        T (*operation)(std::string, std::string, graph::GraphPtr);

        if (is(node->op, "+")) {
            operation = &sum<T>;
        } else if(is(node->op, "-")) {
            operation = &minus<T>;
        } else if(is(node->op, "*")) {
            operation = &mult<T>;
        } else if(is(node->op, "/")) {
            operation = &div<T>;
        } else if(is(node->op, "<<")) {
            operation = &leftShift<T>;
        } else if(is(node->op, ">>")) {
            operation = &rightShift<T>;
        } else if(is(node->op, "<")) {
            operation = &less<T>;
        } else if(is(node->op, "<=")) {
            operation = &lessEq<T>;
        } else if(is(node->op, "==")) {
            operation = &eq<T>;
        } else if(is(node->op, ">=")) {
            operation = &greatEq<T>;
        } else if(is(node->op, ">")) {
            operation = &great<T>;
        } else if(is(node->op, "!=")) {
            operation = &diff<T>;
        } else if(is(node->op ,"&&")) {
            operation = &andBin<T>;
        } else if(is(node->op, "||")) {
            operation = &orBin<T>;
        } else if(is(node->op, "&")) {
            operation = &andBit<T>;
        } else if(is(node->op, "|")) {
            operation = &orBit<T>;
        } else if(is(node->op, "~")) {
            operation = &negBit<T>;
        } else if(is(node->op, "cast")) {
            operation = &cast<T>;
        } else if(is(node->op, "abs")) {
            operation = &abs<T>;
        }

        out = operation(node->incoming[0], node->incoming[1], graph);

        std::string output = syntax::Syntax::getIdentifier(node->out, graph);
        graph->set(output, out);
    }

}

#endif /* BASIC_OPERATIONS_H */