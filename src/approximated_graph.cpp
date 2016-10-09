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

    ApproximatedGraph* ApproximatedGraph::substitute(graph::Nodes replacement, graph::NodePtr old)
    {
        auto copy = new ApproximatedGraph(*this);

        int pos = super::find(old);
        for(auto it = replacement.rbegin(); it != replacement.rend(); it++) {
            copy->insert(*it, pos);
        }
        copy->remove(pos + replacement.size());

        return copy;
    }

    void ApproximatedGraph::rollbackToStart()
    {
        while(this->rollback() != NULL) {
            this->rollback();
        }
    }

}