#ifndef BASIC_OPERATIONS_H
#define BASIC_OPERATIONS_H

#include "graph.h"
#include "syntax.h"
#include "utility.h"


namespace operations {

    template <typename T> inline
    void extractOperand(std::string name, T &op, graph::GraphPtr graph)
    {
        if (isNumber(name)){
            op = std::stod(name, NULL);
        } else if (is(name, "randomFloat")) {
            op = (T) randDouble();
        }else {
            graph->get(syntax::Syntax::getIdentifier(name, graph), op);
        }
    }

    template <> inline
    void extractOperand(std::string name, std::string &op, graph::GraphPtr graph)
    {
        if (isNumber(name)){
            op = std::stod(name, NULL);
        } else if (is(name, "randomFloat")) {
            op = std::to_string(randDouble());
        }else {
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
        int *ptr1 = (int *) (&op1);
        int *ptr2 = (int *) (&op2);
        return (T) ((*ptr1) & (*ptr2));
    }

    template<typename T>
    T orBit(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        int *ptr1 = (int *) (&op1);
        int *ptr2 = (int *) (&op2);
        return (T) ((*ptr1) | (*ptr2));
    }

    template<typename T>
    T negBit(std::string nameOp1, std::string nameOp2, graph::GraphPtr graph)
    {
        T op;
        extractOperand(nameOp1, op, graph);
        int *ptr = (int *) (&op);
        return (T) ~(*ptr);
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