#include "include/executer.h"


namespace executer {

    Executer::Executer()
    {
        this->checker = new syntax::Syntax();
    }

    void Executer::runGraph(graph::GraphPtr graph)
    {
        graph::NodePtr current;
        while ((current = graph->next()) != NULL) {
            runNode(current, graph);
        }
    }

    void Executer::runNode(graph::NodePtr node, graph::GraphPtr graph)
    {
        if (checker->isControlOp(node->out)) {
            runControlOperation(node, graph);
        } else {
            runBasicOperation(node, graph);
        }
    }


    void Executer::runBasicOperation(graph::NodePtr node, graph::GraphPtr graph)
    {
        if (is(graph->getType(), "int")) {
            selectOperation<int>(node, graph);
        } else if (is(graph->getType(), "float")) {
            selectOperation<float>(node, graph);
        } else if (is(graph->getType(), "double")) {
            selectOperation<double>(node, graph);
        }
    }

    void Executer::runControlOperation(graph::NodePtr node, graph::GraphPtr graph)
    {
        int result = evaluateCondition(node, graph);

        if (result) {
            runBlock(node->out, graph);
            completeControlExecution(node, graph);
        } else if (checker->allowsComplementaryBlock(node->out)) {
            runComplementaryBlock(node->out, graph);
            completeControlExecution(node, graph);
        } else {
            skipToEndBlock(node->out, graph);
        }    
    }

    void Executer::completeControlExecution(graph::NodePtr node, graph::GraphPtr graph)
    {
        graph::NodePtr current = graph->rollback();
        if(checker->isLoop(node->out, current->out)) {
            rollbackToStart(node, current, graph);
            runNode(graph->next(), graph);
        } else if(!checker->endsBlock(node->out, current->out)) {
            skipToEndBlock(node->out, graph);
        }
        graph->next();
    }

    void Executer::runComplementaryBlock(std::string opening, graph::GraphPtr graph)
    {
        graph::NodePtr current = graph->next();
        while(!checker->closesBlock(opening, current->out)) {
            current = graph->next();
        }

        if(!checker->endsBlock(opening, current->out)) {
            runControlOperation(current, graph);
        }
    }

    void Executer::runBlock(std::string opening, graph::GraphPtr graph)
    {
        graph::NodePtr current = graph->next();
        while(!checker->closesBlock(opening, current->out)) {
            runNode(current, graph);
            current = graph->next();
        }
    }

    void Executer::skipToEndBlock(std::string control, graph::GraphPtr graph) 
    {
        int depth = -1;
        graph::NodePtr cursor;
        while(depth != 0) {
            cursor = graph->next();

            if (checker->endsBlock(control, cursor->out) && isOpEmpty(cursor)) {
                depth++;
            } else if (is(control, cursor->out) && !isOpEmpty(cursor)) {
                depth--;
            }
        }
    }

    void Executer::rollbackToStart(graph::NodePtr start, graph::NodePtr current, graph::GraphPtr graph)
    {
        graph::NodePtr cursor = graph->rollback();
        while (graph->current() != start) {
            cursor = graph->rollback();
        }
    }

    int Executer::evaluateCondition(graph::NodePtr condition, graph::GraphPtr graph)
    {
        int result;
        runBasicOperation(condition, graph);
        graph->get(condition->out, result);

        return result;
    }

    Executer::~Executer()
    {
        delete(checker);
    }


} // namespace executer