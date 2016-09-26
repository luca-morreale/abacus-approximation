#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <sstream>

#include "node.h"
#include "edge.h"


namespace graph {


    template <typename T> 
    struct Graph {
        std::vector<Node*> nodes;
        Edges edges;
        unsigned int cursor;

        Node *next();
        void append(Node *node);
        T get(std::string key);
        void set(std::string key, T value);
    };


    template <> 
    struct Graph <int> {
        std::vector<Node*> nodes;
        Edges edges;
        unsigned int cursor;

        Node *next();
        void append(Node *node);
        int get(std::string key);
        void set(std::string key, int value);
    };

    template <> 
    struct Graph <double> {
        std::vector<Node*> nodes;
        Edges edges;
        unsigned int cursor;

        Node *next();
        void append(Node *node);
        double get(std::string key);
        void set(std::string key, double value);
    };

    template <> 
    struct Graph <float> {
        std::vector<Node*> nodes;
        Edges edges;
        unsigned int cursor;

        Node *next();
        void append(Node *node);
        float get(std::string key);
        void set(std::string key, float value);
    };

}


#endif /* GRAPH_H */