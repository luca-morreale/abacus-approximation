#include "include/executed_graph.h"


namespace approximation {

    ExecutedGraph::ExecutedGraph(std::string type) : ApproximatedGraph(type)
    { /*   */ }

    ExecutedGraph::ExecutedGraph(const ExecutedGraph &other) : ApproximatedGraph(other.type)
    {
        this->nodes.insert(this->nodes.begin(), other.nodes.begin(), other.nodes.end());
        this->edges.insert(other.edges.begin(), other.edges.end());
    }

    ExecutedGraph::ExecutedGraph(const graph::Graph &other) : ApproximatedGraph(other)
    { /*   */ }

    void ExecutedGraph::setOutput(std::vector<double> output)
    {
        this->output.clear();
        this->output.insert(this->output.begin(), output.begin(), output.end());
    }
    
    double ExecutedGraph::getOutputSum()
    {
        double sum = 0;
        for (auto it = this->output.begin(); it != this->output.end(); it++) {
            sum += *it;
        }
        return sum;
    }

}
