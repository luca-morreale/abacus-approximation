#include "include/approximated_graph.h"


namespace approximation {

    ApproximatedGraph::ApproximatedGraph(std::string type) : Graph(type)
    { /*   */ }

    ApproximatedGraph::ApproximatedGraph(const ApproximatedGraph &other) : Graph(other.type)
    {
        this->nodes.insert(this->nodes.begin(), other.nodes.begin(), other.nodes.end());
        this->edges.insert(other.edges.begin(), other.edges.end());
    }

    ApproximatedGraph::ApproximatedGraph(const graph::Graph &other) : Graph(other)
    { /*   */ }

    void ApproximatedGraph::substitute(graph::Nodes replacement, graph::NodePtr old)
    {
        int pos = super::find(old);
        for(graph::NodeIterator it = replacement.end(); it != replacement.begin(); it--) {
            super::insert(*it, pos);
        }
        super::remove(pos + replacement.size());
    }

}