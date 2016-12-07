#ifndef EXECUTED_GRAPH_H
#define EXECUTED_GRAPH_H

#include "approximated_graph.h"


namespace approximation {

    class ExecutedGraph : public ApproximatedGraph {
    public:
        ExecutedGraph(std::string type);
        ExecutedGraph(const graph::Graph &other);
        ExecutedGraph(const ExecutedGraph &other);
        ~ExecutedGraph() { }

        void setOutput(std::vector<double> output);
        double getOutputSum();

    private:

        std::vector<double> output;

        typedef ApproximatedGraph super;

    };

    typedef ExecutedGraph * ExecutedGraphPtr;

}



#endif /* EXECUTED_GRAPH_H */
