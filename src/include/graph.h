#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <sstream>

#include "node.h"
#include "edge.h"


namespace graph {

    struct Graph {
        Nodes nodes;
        Edges edges;
        unsigned int cursor;
        std::string type;
    };

    typedef Graph* GraphPtr;

    GraphPtr newGraph(std::string type);

    NodePtr next(GraphPtr graph);
    void appendToGraph(GraphPtr graph, NodePtr node);
    void addEdges(GraphPtr graph, NodePtr node);
    void set(GraphPtr graph, std::string key, int value);
    void set(GraphPtr graph, std::string key, float value);
    void set(GraphPtr graph, std::string key, double value);

}


#endif /* GRAPH_H */