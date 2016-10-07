#ifndef APPROXIMATED_GRAPH_H
#define APPROXIMATED_GRAPH_H

#include "graph.h"


namespace approximation {

    class ApproximatedGraph : public graph::Graph {
    public:
        ApproximatedGraph(std::string type) : Graph(type) { }
        ApproximatedGraph(const graph::Graph &other);
        ApproximatedGraph(const ApproximatedGraph &other);
        ~ApproximatedGraph() { }

        void substitute(graph::Nodes replacement, graph::NodePtr old);

    private:
        ApproximatedGraph() : Graph() { }


        typedef graph::Graph super;

    };

    typedef ApproximatedGraph * ApproximatedGraphPtr;

}



#endif /* APPROXIMATED_GRAPH_H */