#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <cstdlib>
#include <map>
#include <sstream>
#include <string>

#include "edge.h"
#include "node.h"

#ifdef DEBUG
    #include <iostream>
#endif


namespace graph {

    class Graph {

    public:
        Graph(std::string type);
        Graph(const Graph &other);
        ~Graph();
        
        /**
         * Appends the node to the graph and add new edges.
         * NodePtr node     node to add
         */
        void appendToGraph(NodePtr node);

        /**
         * Returns the next node to be executed.
         */
        NodePtr next();

        /**
         * Returns the previous exectued node.
         */
        NodePtr rollback();

        NodePtr current();

        /**
         * Sets the value of the given edge.
         * key      identifier of the edge
         * out      value to set
         */
        void set(std::string key, int value);
        void set(std::string key, float value);
        void set(std::string key, double value);

        /**
         * Gets the value of the given edge.
         * key      identifier of the edge
         * out      reference to the ouput variable
         */
        void get(std::string key, int &out);
        void get(std::string key, float &out);
        void get(std::string key, double &out);
        void get(std::string key, std::string &out);

        std::string getType();
        
        /**
         * Returns all the name of the edges which contains 'output' as name.
         */
        std::vector<std::string> getOutputList();

        #ifdef DEBUG
            void debug();
        #endif

    protected:
        Graph();
        void insert(NodePtr node, int pos);
        int find(NodePtr item);
        void remove(int pos);

        Nodes nodes;
        Edges edges;
        unsigned int cursor;
        std::string type;


    private:
        
        void addEdges(NodePtr node);

        bool isValidNode(NodePtr node);
        bool isNewEdge(std::string edge);
        bool isValidEdge(std::string edge);

    };

    typedef Graph* GraphPtr;

}


#endif /* GRAPH_H */