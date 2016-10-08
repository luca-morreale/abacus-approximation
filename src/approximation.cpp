#include "include/approximation.h"


namespace approximation {

    std::vector<Approximation> approximations(approx_values, approx_values + map_start_values_size);

    std::map<Approximation, std::string> approximationsOp(op_start_values, op_start_values + op_map_values_size);


    graph::Nodes selectSuitableNodes(graph::GraphPtr graph, Approximation approximation)
    {
        if(approximation == approximateValue) {
            return selectAll(graph);
        } else {
            return selectOperation(graph, approximationsOp[approximation]);
        }
    }

    graph::Nodes selectOperation(graph::GraphPtr graph, std::string op)
    {
        graph::Nodes suitableNodes;
        graph::NodePtr current;
        while ((current=graph->next()) != NULL) {
            if (is(current->op, op)) {
                suitableNodes.push_back(current);
            }
        }
        return suitableNodes;
    }

    graph::Nodes selectAll(graph::GraphPtr graph)
    {
        graph::Nodes suitableNodes;
        graph::NodePtr current;
        while ((current=graph->next()) != NULL) {
            if (!syntax::Syntax::isControlOp(current->out)) {
                suitableNodes.push_back(current);
            }
        }
        return suitableNodes;
    }
    
    
    graph::Nodes approximateSum(graph::NodePtr node)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement[0]->op = "|";
        return replacement;
    }

    graph::Nodes approximateMinus(graph::NodePtr node)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement.push_back(graph::newNode(node));

        replaceOperations(replacement, "~", "&", replacement[0]->incoming[1]);

        return replacement;
    }

    graph::Nodes approximateMult(graph::NodePtr node)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement.push_back(graph::newNode(node));

        replaceOperations(replacement, "<<", "+", calculateShift());

        return replacement;
    }
    
    graph::Nodes approximateDiv(graph::NodePtr node)
    {
        graph::Nodes replacement;
        replacement.push_back(graph::newNode(node));
        replacement.push_back(graph::newNode(node));

        replaceOperations(replacement, ">>", "-", calculateShift());

        return replacement;
    }

    graph::Nodes approximateValue(graph::NodePtr node)  // put how many bit to zero?
    {

    }

    void replaceOperations(graph::Nodes &replacement, std::string op1, std::string op2, std::string operand)
    {
        replacement[0]->op = op1;
        replacement[0]->out = "tmp";
        replacement[0]->incoming[1] = operand;

        replacement[1]->op = op2;
        replacement[1]->incoming[0] = "tmp";
    }

    std::string calculateShift()
    {

        return 0 + "";
    }

    void doubleIncrement(graph::Nodes &replacement)
    {
        if(isNumber(replacement[0]->incoming[0])) {
            int index = std::stoi(replacement[0]->incoming[0]) * 2;
            replacement[0]->incoming[0] = index + "";
        } else {
            int index = std::stoi(replacement[0]->incoming[1]) * 2;
            replacement[0]->incoming[1] = index + "";
        }
    }

    

}