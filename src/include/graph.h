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

        NodePtr next();
        void appendToGraph(NodePtr node);
        void addEdges(NodePtr node);
        void set(std::string key, int value);
        void set(std::string key, float value);
        void set(std::string key, double value);
        void get(std::string key, int &out);
        void get(std::string key, float &out);
        void get(std::string key, double &out);
    };

    typedef Graph* GraphPtr;

    GraphPtr newGraph(std::string type);

}


#endif /* GRAPH_H */