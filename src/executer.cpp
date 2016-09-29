#include "include/executer.h"


namespace executer {

    double runGraph(graph::GraphPtr graph)
    {
        graph::NodePtr current;
        while ((current = graph->next()) != NULL) {
            runNode(current, graph);
        }

    }

    void runNode(graph::NodePtr node, graph::GraphPtr graph)
    {
        if (isControlOp(node->op)) {

        } else {
            //executeOperation();

            if (graph->getType().compare("int")) {
                selectOperation<int>(node, graph);
            } else if (graph->getType().compare("float")) {
                selectOperation<float>(node, graph);
            } else if (graph->getType().compare("double")) {
                selectOperation<double>(node, graph);
            }

            
        }

    }

    bool isControlOp(std::string op)
    {
        if (op[0] == '_') {
            return true;
        }
        return false;
    }


    bool isNumber(const std::string &str)
    {
        return !str.empty() && str.find_first_not_of(".0123456789") == std::string::npos;
    }


}