#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <sstream>

#include "node.h"
#include "edge.h"


namespace graph {

    template <typename T> 
    struct Graph {
        Nodes nodes;
        Edges edges;
        unsigned int cursor;

        Node *next();
        void append(Node *node);
        T get(std::string key);
        void set(std::string key, T value);
    };


    template <> 
    struct Graph <int> {
        Nodes nodes;
        Edges edges;
        unsigned int cursor;

        Node *next();
        void append(Node *node);
        int get(std::string key);
        void set(std::string key, int value);
    };

    template <> 
    struct Graph <double> {
        Nodes nodes;
        Edges edges;
        unsigned int cursor;

        Node *next();
        void append(Node *node);
        double get(std::string key);
        void set(std::string key, double value);
    };

    template <> 
    struct Graph <float> {
        Nodes nodes;
        Edges edges;
        unsigned int cursor;

        Node *next();
        void append(Node *node);
        float get(std::string key);
        void set(std::string key, float value);
    };

    template <typename T> using GraphPtr = Graph<T> *;

    template <typename T> 
    inline GraphPtr<T> newGraph()
    {
        GraphPtr<T> graph = (GraphPtr<T>) malloc(sizeof(Graph<T>));
        graph->cursor = 0;
        return graph;
    }

}


#endif /* GRAPH_H */