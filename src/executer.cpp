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
        if (isControlOp(node->out)) {
            runControlOperation(node, graph);
        } else {
            runBasicOperation(node, graph);
        }
    }


    void runBasicOperation(graph::NodePtr node, graph::GraphPtr graph)
    {
        if (is(graph->getType(), "int")) {
            selectOperation<int>(node, graph);
        } else if (is(graph->getType(), "float")) {
            selectOperation<float>(node, graph);
        } else if (is(graph->getType(), "double")) {
            selectOperation<double>(node, graph);
        }
    }

    void runControlOperation(graph::NodePtr node, graph::GraphPtr graph)
    {
        int result;
        runBasicOperation(node, graph);
        graph->get(node->out, result);

        if (result) {
            runBlock(node->out, graph);
        } else if (allowsComplementaryBlock(node->out)) {
            runComplementaryBlock(node->out, graph);
        }

        graph::NodePtr current = graph->rollback();
        if(!isEndBlock(node->out, current)) {
            skipToEndBlock(node->out, graph);
        }
    }

    void runComplementaryBlock(std::string opening, graph::GraphPtr graph)
    {
        graph::NodePtr current = graph->next();
        while(!isComplementaryClosing(opening, current->out) && !isEndBlock(opening, current)) {
            current = graph->next();
        }

        if(!isEndBlock(opening, current)) {
            runControlOperation(current, graph);
        }
    }

    void runBlock(std::string opening, graph::GraphPtr graph)
    {
        graph::NodePtr current = graph->next();
        while(!isCloseBlock(opening, current)) {
            runNode(current, graph);
            current = graph->next();
        }
    }

    void skipToEndBlock(std::string control, graph::GraphPtr graph) 
    {
        int depth = -1;
        graph::NodePtr cursor;
        while(depth != 0) {
            cursor = graph->next();

            if (isEndBlock(control, cursor)) {
                depth++;
            } else if (is(control, cursor->out) && !emptyOp(cursor)) {
                depth--;
            }
        }
    }


    bool isCloseBlock(std::string opening, graph::NodePtr node)
    {
        if(isEndBlock(opening, node) || isComplementaryClosing(opening, node->out)) {
            return true;
        } else if(isDoWhile(opening, node->out) && emptyOp(node)) {
            return true;
        }
        return false;
    }

    bool isEndBlock(std::string opening, graph::NodePtr node)
    {
        return (is(opening, node->out) || isComplementaryEnding(opening, node->out)) && emptyOp(node);
    }

    bool isComplementaryEnding(std::string opening, std::string current)
    {
        return (is(opening, "_elseif") || is(opening, "_else")) && is(current, "_if");
    }

    bool isComplementaryClosing(std::string opening, std::string current)
    {
        if(allowsComplementaryBlock(opening)){
            return is(current, "_elseif") || is(current, "_else");
        }
        return false;
    }

    bool isDoWhile(std::string opening, std::string closing)
    {
        return is(opening, "_do") && is(closing, "_while");
    }

    bool allowsComplementaryBlock(std::string control)
    {
        return is(control, "_if") || is(control, "_elseif");
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

    bool is(std::string a, std::string b)
    {
        return a.compare(b) == 0;
    }

    bool emptyOp(graph::NodePtr node)
    {
        return is(node->op, "") || node->op.size() == 0;
    }


}