#ifndef EXECUTER_H
#define EXECUTER_H


#include <iostream>
#include <string>
#include "graph.h"
#include "syntax.h"


namespace executer {

    class Executer {

    public:
        Executer();
        ~Executer() { }

        double runGraph(graph::GraphPtr graph);
        double runabacusApproximation(graph::GraphPtr graph);

        void runNode(graph::NodePtr node, graph::GraphPtr graph);
        void runBasicOperation(graph::NodePtr node, graph::GraphPtr graph);

        /**
         * Runs the control structure; after the execution the next instruction 
         * will be the one following the entire control block.
         */
        void runControlOperation(graph::NodePtr node, graph::GraphPtr graph);

        /**
         * Skips to the complementary structure if exists and then executes it.
         */
        void runComplementaryBlock(std::string opening, graph::GraphPtr graph);

        /**
         * Runs a control block, at the end do not skip to the end of the structure.
         */
        void runBlock(std::string opening, graph::GraphPtr graph);

        /**
         * Skips to the end of the control structure.
         */
        void skipToEndBlock(std::string control, graph::GraphPtr graph);


        void completeControlExecution(graph::NodePtr node, graph::GraphPtr graph);

        void rollbackToStart(graph::NodePtr start, graph::NodePtr current, graph::GraphPtr graph);
        void rollbackBefore(graph::NodePtr start, graph::GraphPtr graph);


    private:
        syntax::SyntaxPtr checker;

        int evaluateCondition(graph::NodePtr condition, graph::GraphPtr graph);

        bool isDoWhile(std::string opening, std::string closing);
        
        bool emptyOp(graph::NodePtr node);

    };


    bool is(std::string a, std::string b);
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
        T op1, op2;
        getOperands(nameOp1, op1, nameOp2, op2, graph);
        return (T) op2;
    }

    template<typename T>
    void selectOperation(graph::NodePtr node, graph::GraphPtr graph)
    {
        T out;
        T (*operation)(std::string, std::string, graph::GraphPtr);

        if (is(node->out, "_do")) { // fake calculation of condition to result true
            operation = &eq<T>;
            node->incoming[0] = "1";
            node->incoming[1] = "1";
        } else if (is(node->op, "+")) {
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
        } else if(is(node->op, "<<c")) {
            operation = &cast<T>;
        }

        out = operation(node->incoming[0], node->incoming[1], graph);

        graph->set(node->out, out);
    }


}  // namespace executer


#endif /* EXECUTER_H */