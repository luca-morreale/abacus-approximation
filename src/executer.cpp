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
            operations::selectOperation<int>(node, graph);
        } else if (is(graph->getType(), "float")) {
            operations::selectOperation<float>(node, graph);
        } else if (is(graph->getType(), "double")) {
            operations::selectOperation<double>(node, graph);
        }
    }

    void Executer::runControlOperation(graph::NodePtr node, graph::GraphPtr graph)
    {
        if(isOpEmpty(node)) {       // _else case
            runBlock(node->out, graph);
        } else if (checker->isLoop(node->out)) {
            runLoop(node, graph);
        } else {
            int result = evaluateCondition(node, graph);

            if(result) {
                runBlock(node->out, graph);
            } else if (!result && checker->allowsComplementaryBlock(node->out)) {
                runComplementaryBlock(node->out, graph);
            } else if(!result) {
                skipToEndBlock(node->out, graph);
            }
        }
    }

    void Executer::runLoop(graph::NodePtr start, graph::GraphPtr graph)
    {
        int condition = evaluateCondition(start, graph);
        while(condition) {
            runBlock(start->out, graph);
            rollbackToStart(graph->rollback(), graph);
            condition = evaluateCondition(graph->current(), graph);
            graph->next();
        }
        skipToEndBlock(start->out, graph);
    }

    void Executer::runComplementaryBlock(std::string opening, graph::GraphPtr graph)
    {
        graph::NodePtr current = graph->next();
        while(!checker->closesBlock(opening, current)) {
            current = graph->next();
        }

        if(!checker->endsBlock(opening, current)) {
            runControlOperation(current, graph);
        }
    }

    void Executer::runBlock(std::string opening, graph::GraphPtr graph)
    {
        graph::NodePtr current = graph->next();
        while(!checker->closesBlock(opening, current)) {
            runNode(current, graph);
            current = graph->next();
        }

        graph->rollback();
        skipToEndBlock(opening, graph);
    }

    void Executer::skipToEndBlock(std::string control, graph::GraphPtr graph) 
    {
        int depth = -1;
        graph::NodePtr cursor;
        while(depth != 0) {
            cursor = graph->next();

            if (checker->endsBlock(control, cursor)) {
                depth++;
            } else if (is(control, cursor->out) && checker->startsNewBlock(cursor)) {
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

    void Executer::rollbackToStart(graph::NodePtr end, graph::GraphPtr graph)
    {
        int depth = 1;
        graph::NodePtr cursor;
        while(depth != 0) {
            cursor = graph->rollback();

            if (checker->endsBlock(cursor->out, end) && checker->startsNewBlock(cursor)) {
                depth--;
            } else if(is(cursor->out, end->out) && isOpEmpty(cursor)) {
                depth++;
            }
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