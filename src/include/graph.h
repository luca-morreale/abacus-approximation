#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <sstream>
#include <cstdlib>
#include <map>

#include "node.h"
#include "edge.h"

#ifdef DEBUG
    #include <iostream>
#endif


namespace graph {

    typedef struct Graph {
        Nodes nodes;
        Edges edges;
        unsigned int cursor;
        std::string type;

        NodePtr next();
        void appendToGraph(NodePtr node);
        void addEdges(NodePtr node);
        void set(std::string key, int value);
        void set(std::string key, float value);
        void set(std::string key, double value);
        void get(std::string key, int &out);
        void get(std::string key, float &out);
        void get(std::string key, double &out);
    } Graph;

    typedef Graph* GraphPtr;

    GraphPtr newGraph(std::string type);

    #ifdef DEBUG
        void debug(GraphPtr graph);
    #endif

}


#endif /* GRAPH_H */