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

    class Graph {

    public:
        Graph(std::string type);
        ~Graph();
        
        void appendToGraph(NodePtr node);

        NodePtr next();

        void set(std::string key, int value);
        void set(std::string key, float value);
        void set(std::string key, double value);

        void get(std::string key, int &out);
        void get(std::string key, float &out);
        void get(std::string key, double &out);

        std::string getType();

        #ifdef DEBUG
            void debug();
        #endif


    private:
        Nodes nodes;
        Edges edges;
        unsigned int cursor;
        std::string type;

        Graph();

        void addEdges(NodePtr node);

        bool isValidNode(NodePtr node);
        bool isNewEdge(std::string edge);
        bool isValidEdge(std::string edge);

    };

    typedef Graph* GraphPtr;

}


#endif /* GRAPH_H */